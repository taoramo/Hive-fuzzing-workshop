/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 10:43:21 by toramo            #+#    #+#             */
/*   Updated: 2024/01/02 10:43:22 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	vec_free(t_vec *src)
{
	if (!src || src->alloc_size == 0)
		return ;
	if (src->memory)
		free(src->memory);
	ft_bzero(src, sizeof(t_vec));
}

int	vec_from(t_vec *dst, void *src, size_t len, size_t elem_size)
{
	if (!dst || !src || elem_size == 0)
		return (-1);
	else if (vec_new(dst, len, elem_size) <= 0)
		return (-1);
	ft_memcpy(dst->memory, src, dst->alloc_size);
	dst->len = len;
	return (1);
}

int	vec_copy(t_vec *dst, t_vec *src)
{
	size_t	to_copy;

	if (!dst || !src || !src->memory)
		return (-1);
	if (!dst->memory)
		if (vec_new(dst, src->len, src->elem_size) <= 0)
			return (-1);
	if (src->len * src->elem_size < dst->alloc_size)
		to_copy = src->len * src->elem_size;
	else
		to_copy = dst->alloc_size;
	ft_memcpy(dst->memory, src->memory, to_copy);
	dst->len = to_copy / dst->elem_size;
	return (dst->alloc_size);
}

void	*vec_get(t_vec *src, size_t index)
{
	if (!src)
		return (0);
	if (!src->memory)
		return (0);
	if (index >= src->len)
		return (0);
	return (&src->memory[src->elem_size * index]);
}

int	vec_clear(t_vec *src)
{
	if (!src)
		return (-1);
	ft_bzero(src->memory, src->len);
	src->len = 0;
	return (0);
}
