/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:44:45 by toramo            #+#    #+#             */
/*   Updated: 2024/02/09 16:44:47 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_vec *argv)
{
	char	str[MAXPATHLEN];
	char	*check;

	(void)argv;
	check = getcwd(str, MAXPATHLEN);
	if (!check)
	{
		ft_putstr_fd("minishell: pwd:", 2);
		ft_putstr_fd(str, 2);
		perror(0);
		return (-1);
	}
	else
	{
		ft_putstr_fd(str, 1);
		write(1, "\n", 1);
		return (0);
	}
}

int	contains_equals(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	ft_env(t_vec *env)
{
	size_t	i;

	i = 0;
	while (i < env->len)
	{
		if (contains_equals(*(char **)vec_get(env, i)))
			ft_putstr_fd(*(char **)vec_get(env, i), 1);
		write(1, "\n", 1);
		i++;
	}
	return (0);
}

void	unset_variable(t_vec *env, char *arg)
{
	size_t	i;
	int		j;
	char	**strs;

	i = 0;
	j = 0;
	strs = (char **)env->memory;
	while (i < env->len)
	{
		while (strs[i][j] && strs[i][j] != '=')
			j++;
		if (!ft_strncmp(arg, strs[i], j))
		{
			free(strs[i]);
			vec_remove(env, i);
		}
		j = 0;
		i++;
	}
}

int	ft_unset(t_vec *argv, t_vec *env)
{
	size_t	i;
	char	**args;

	i = 1;
	args = (char **)argv->memory;
	if (argv->len < 2)
		return (0);
	while (i < argv->len)
	{
		unset_variable(env, args[i]);
		i++;
	}
	return (0);
}
