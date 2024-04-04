/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expanded_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:09:53 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/13 10:17:16 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int	replace_argv(t_vec *argv, t_vec *src, size_t i)
{
	size_t	j;
	
	free( *(char **) vec_get(argv, i));
	vec_remove(argv, i);
	j = 0;
	while (j < src->len)
	{
		if (vec_insert(argv, (char **) vec_get(src, j), i + j) < 0)
			return (free_split_vec(argv));
		j++;
	}
	return (1);
}

int	split_expanded_command(t_vec *argv)
{
	t_vec	split;
	size_t	i;
	

	i = 0;
	while (i < argv->len)
	{
		if (vec_new(&split, 0, sizeof(char *)) == -1)
			return (-1);
		split_command(&split, *(char **) vec_get(argv, i));
		if (split.len > 1)
		{
			replace_argv(argv, &split, i);
			i += split.len - 1;
			vec_free(&split);
		}
		else
			free_split_vec(&split);
		i++;
	}
	return (1);
}
