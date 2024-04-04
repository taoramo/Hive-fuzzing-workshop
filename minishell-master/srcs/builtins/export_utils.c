/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:04:39 by toramo            #+#    #+#             */
/*   Updated: 2024/02/14 11:04:40 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_entry_exists(char *str, t_vec *env)
{
	size_t	i;
	char	**entries;

	entries = (char **)env->memory;
	i = 0;
	while (i < env->len)
	{
		if (!ft_strncmp(str, entries[i], ft_strlen_member(str, '=')))
			return (1);
		i++;
	}
	return (0);
}

int	remove_entry(char *str, t_vec *env)
{
	size_t	i;
	char	**entries;

	entries = (char **)env->memory;
	i = 0;
	while (i < env->len)
	{
		if (!ft_strncmp(str, entries[i], ft_strlen_member(str, '=')))
		{
			vec_remove(env, i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	contains_plusequals(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] && i > 0 && str[i - 1] == '+')
		return (1);
	return (0);
}
