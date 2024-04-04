/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:44:33 by toramo            #+#    #+#             */
/*   Updated: 2024/02/09 16:44:35 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_echo(t_vec *argv, size_t i, int print_nl)
{
	int		r;
	char	**strs;

	strs = (char **)argv->memory;
	while (i < argv->len)
	{
		r = ft_putstr_fd(strs[i], 1);
		if (r == -1)
			return (1);
		if (i < argv->len - 1)
			r = write(1, " ", 1);
		if (r == -1)
			return (1);
		i++;
	}
	if (print_nl)
		write(1, "\n", 1);
	return (0);
}

int	ft_echo(t_vec *argv)
{
	char	**strs;
	size_t	i;
	int		print_nl;

	strs = (char **)argv->memory;
	if (!strs[1])
	{
		write(1, "\n", 1);
		return (0);
	}
	if (!ft_strncmp(strs[1], "-n", 3))
	{
		print_nl = 0;
		i = 2;
	}
	else
	{
		print_nl = 1;
		i = 1;
	}
	return (print_echo(argv, i, print_nl));
}

char	*ft_getenv(char *arg, t_vec *env)
{
	size_t	i;
	int		j;
	char	**entries;
	char	*str;

	entries = (char **)env->memory;
	i = 0;
	j = 0;
	while (i < env->len)
	{
		if (!ft_strncmp(arg, entries[i], ft_strlen_member(entries[i], '='))
			&& arg[ft_strlen_member(entries[i], '=')] == 0)
		{
			while (entries[i][j] && entries[i][j] != '=')
				j++;
			j++;
			str = ft_calloc(ft_strlen(&entries[i][j]) + 1, sizeof(char));
			if (!str)
				return (0);
			ft_strlcpy(str, &entries[i][j], ft_strlen(&entries[i][j]) + 1);
			return (str);
		}
		i++;
	}
	return (0);
}
