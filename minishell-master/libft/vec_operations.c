/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 10:49:33 by toramo            #+#    #+#             */
/*   Updated: 2024/01/02 10:49:34 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	vec_insert(t_vec *dst, void *src, size_t index)
{
	if (!src || !src || index > dst->len)
		return (-1);
	else if (index == dst->len)
	{
		return (vec_push(dst, src));
	}
	if (dst->alloc_size <= (dst->len) * dst->elem_size)
	{
		if (vec_resize(dst, 2 * dst->alloc_size) <= 0)
			return (-1);
	}
	ft_memmove(&dst->memory[(index + 1) * dst->elem_size],
		&dst->memory[index * dst->elem_size],
		(dst->len - index) * dst->elem_size);
	ft_memcpy(vec_get(dst, index), src, dst->elem_size);
	dst->len++;
	return (dst->len);
}

int	vec_remove(t_vec *src, size_t index)
{
	if (!src || index >= src->len)
		return (-1);
	else if (index + 1 == src->len)
	{
		ft_bzero(vec_get(src, src->len - 1), src->elem_size);
		src->len--;
		return (1);
	}
	ft_memmove(vec_get(src, index),
		&src->memory[src->elem_size * (index + 1)],
		(src->len - index - 1) * src->elem_size);
	ft_bzero(vec_get(src, src->len - 1), src->elem_size);
	src->len--;
	return (src->len);
}

int	vec_append(t_vec *dst, t_vec *src)
{
	if (!src || !dst || !src->memory)
		return (-1);
	if (dst->alloc_size < (dst->len + src->len) * dst->elem_size)
	{
		if (vec_resize(dst, dst->alloc_size + src->alloc_size) <= 0)
			return (-1);
	}
	ft_memcpy(&dst->memory[dst->elem_size * dst->len],
		src->memory,
		src->len * src->elem_size);
	dst->len += src->len;
	return (dst->len);
}

int	vec_prepend(t_vec *dst, t_vec *src)
{
	if (!src || !dst || !src->memory)
		return (-1);
	if (dst->alloc_size < (dst->len + src->len) * dst->elem_size)
	{
		if (vec_resize(dst, dst->alloc_size + src->alloc_size) <= 0)
			return (-1);
	}
	ft_memmove(&dst->memory[dst->elem_size * dst->len],
		dst->memory,
		dst->len * dst->elem_size);
	ft_memcpy(dst->memory, src->memory, src->len * dst->elem_size);
	dst->len += src->len;
	return (dst->len);
}

int	vec_dup(t_vec *dst, t_vec *src)
{
	if (!src || !dst)
		return (-1);
	ft_memcpy(dst, src, sizeof(t_vec));
	dst->memory = ft_calloc(dst->alloc_size, 1);
	if (!dst->memory)
		return (-1);
	ft_memcpy(dst->memory, src->memory, src->alloc_size);
	return (0);
}
