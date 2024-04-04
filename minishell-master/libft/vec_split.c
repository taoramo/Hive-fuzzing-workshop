/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 09:48:48 by toramo            #+#    #+#             */
/*   Updated: 2023/10/31 12:59:15 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	vec_free_if_exists(void *arg)
{
	char	*str;

	str = *(char **) arg;
	if (str)
	{
		free(str);
		str = 0;
	}
}

int	free_split_vec(t_vec *strs)
{
	vec_iter(strs, vec_free_if_exists);
	vec_free(strs);
	return (1);
}

void	vec_print_elem_str(void *elem)
{
	ft_printf("%s\n", *(char **)elem);
}

int	vec_split(t_vec *dst, const char *s, char c)
{
	int		j;
	char	*str;

	j = 0;
	if (dst == 0)
		return (-1);
	if (dst->elem_size != sizeof(char *))
		return (-1);
	while (s[j])
	{
		if (s[j] == c)
			j++;
		else
		{
			str = ft_substr(s, j, ft_strlen_member(&s[j], c));
			if (!str)
				return (free_split_vec(dst));
			if (vec_push(dst, &str) < 0)
				return (free_split_vec(dst));
			j = j + ft_strlen_member(&s[j], c);
		}
	}
	return (0);
}
