/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 10:49:19 by toramo            #+#    #+#             */
/*   Updated: 2024/01/02 10:49:20 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	vec_new(t_vec *dst, size_t init_len, size_t elem_size)
{
	if (elem_size == 0)
		return (-1);
	dst->elem_size = elem_size;
	dst->len = 0;
	dst->alloc_size = init_len * elem_size;
	if (init_len == 0)
	{
		dst->memory = 0;
		return (1);
	}
	else
		dst->memory = ft_calloc(elem_size, init_len);
	if (!dst->memory)
		return (-1);
	else
		return (1);
}

int	vec_resize(t_vec *src, size_t target_size)
{
	void	*new;

	if (!src)
		return (-1);
	if (target_size == src->alloc_size)
		return (1);
	new = ft_calloc(target_size, 1);
	if (!new)
		return (-1);
	if (src->len * src->elem_size > target_size)
	{
		src->len = target_size / src->elem_size;
		ft_memcpy(new, src->memory, target_size);
	}
	else
		ft_memcpy(new, src->memory, src->len * src->elem_size);
	free(src->memory);
	src->memory = new;
	src->alloc_size = target_size;
	return (target_size);
}

int	vec_push(t_vec *dst, void *src)
{
	if (!dst || !src)
		return (-1);
	else if (!dst->memory)
		if (vec_new(dst, 1, dst->elem_size) < 0)
			return (-1);
	if (dst->alloc_size < (dst->len + 1) * dst->elem_size)
	{
		if (vec_resize(dst, 2 * dst->alloc_size) <= 0)
			return (-1);
	}
	ft_memcpy(&dst->memory[dst->elem_size * dst->len], src, dst->elem_size);
	dst->len++;
	return (1);
}

int	vec_pop(void *dst, t_vec *src)
{
	if (!dst || !src)
		return (-1);
	else if (!src->memory || src->len == 0)
		return (0);
	ft_memcpy(dst, &src->memory[src->elem_size * (src->len - 1)],
		src->elem_size);
	ft_bzero(&src->memory[src->elem_size * (src->len - 1)], src->elem_size);
	src->len--;
	return (src->len);
}
