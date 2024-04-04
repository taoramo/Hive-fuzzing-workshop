/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:00:23 by toramo            #+#    #+#             */
/*   Updated: 2024/02/09 17:00:25 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_dir_entries(t_vec *pathstrs)
{
	size_t	i;
	char	**dirs;

	dirs = (char **)pathstrs->memory;
	i = 0;
	while (i < pathstrs->len)
	{
		if (i != 0 && !ft_strncmp(dirs[i], "..", 3))
		{
			free(dirs[i]);
			vec_remove(pathstrs, i);
			free(dirs[i - 1]);
			vec_remove(pathstrs, i - 1);
			i--;
		}
		else if (!ft_strncmp(dirs[i], ".", 2) || (i == 0
				&& !ft_strncmp(dirs[i], "..", 3)))
		{
			free(dirs[i]);
			vec_remove(pathstrs, i);
			i--;
		}
		i++;
	}
}

char	*parse_directory(t_vec *pathstrs)
{
	size_t		i;
	char		*path;

	path = ft_calloc(sizeof(char), MAXPATHLEN);
	if (!path)
		return (0);
	remove_dir_entries(pathstrs);
	path[0] = '/';
	i = 0;
	while (i < pathstrs->len)
	{
		ft_strlcat(path, *(char **)vec_get(pathstrs, i), MAXPATHLEN);
		ft_strlcat(path, "/", MAXPATHLEN);
		i++;
	}
	return (path);
}

char	*construct_path(t_vec *argv)
{
	t_vec	pathstrs;
	char	*buffer;

	buffer = 0;
	if (vec_new(&pathstrs, 32, sizeof(char *)) < 0)
		return (0);
	if (ft_strncmp(*(char **)vec_get(argv, 1), "/", 1))
	{
		buffer = getcwd(0, MAXPATHLEN);
		if (!buffer)
			return (cd_error("memory_error"));
		if (vec_split(&pathstrs, buffer, '/') < 0)
			return (cd_error("memory_error"));
		free(buffer);
	}
	if (vec_split(&pathstrs, *(char **)vec_get(argv, 1), '/') < 0)
	{
		free_split_vec(&pathstrs);
		return (cd_error("memory_error"));
	}
	buffer = parse_directory(&pathstrs);
	free_split_vec(&pathstrs);
	if (!buffer)
		return (cd_error("memory_error"));
	return (buffer);
}

void	change_directory(t_vec *argv, t_vec *env, int *r)
{
	char	**strs;
	char	*path;

	strs = (char **)argv->memory;
	if (strs[1] && ft_strlen(strs[1]))
	{
		path = construct_path(argv);
		if (!path)
		{
			ft_putstr_fd("minishell: cd: path too long\n", 2);
		}
	}
	else
	{
		path = ft_getenv("HOME", env);
		if (!path)
		{
			ft_putstr_fd("minishell: cd: error\n", 2);
		}
	}
	*r = chdir(path);
	free(path);
}

int	ft_cd(t_vec *argv, t_vec *env)
{
	char	**strs;
	int		r;

	strs = (char **)argv->memory;
	if (!strs[1])
		return (0);
	if (strs[1] && ft_strlen(strs[1]) > MAXPATHLEN)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(strs[1], 2);
		ft_putstr_fd(": File name too long\n", 2);
		return (1);
	}
	change_directory(argv, env, &r);
	if (r == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(strs[1]);
		return (1);
	}
	return (r);
}
