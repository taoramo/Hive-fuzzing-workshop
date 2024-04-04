/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_iterators.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 10:42:38 by toramo            #+#    #+#             */
/*   Updated: 2024/01/02 10:42:39 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	vec_iter(t_vec *src, void (*f) (void *))
{
	size_t	i;

	i = 0;
	while (i < src->len)
	{
		f(vec_get(src, i));
		i++;
	}
}

int	vec_map(t_vec *dst, t_vec *src, void (*f) (void *))
{
	if (vec_new(dst, src->len, src->elem_size) <= 0)
		return (-1);
	if (vec_copy(dst, src) < 0)
		return (-1);
	vec_iter(dst, f);
	return (1);
}

int	vec_filter(t_vec *dst, t_vec *src, int (*f) (void *))
{
	size_t	i;

	i = 0;
	while (i < src->len)
	{
		if (f(vec_get(src, i)))
			if (vec_push(dst, vec_get(src, i)) <= 0)
				return (-1);
		i++;
	}
	return (1);
}

void	vec_reduce(void *acc, t_vec *src, void (*f) (void *, void *))
{
	size_t	i;

	i = 0;
	while (i < src->len)
	{
		f(acc, vec_get(src, i));
		i++;
	}
}

void	*vec_find(t_vec *src, int (*f) (void *))
{
	void	*ptr;
	size_t	i;

	if (!src || !src->memory)
		return (0);
	i = 0;
	while (i < src->len)
	{
		ptr = vec_get(src, i);
		if (f(ptr))
			return (ptr);
		i++;
	}
	return (0);
}
