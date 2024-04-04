/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_quicksort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 10:49:42 by toramo            #+#    #+#             */
/*   Updated: 2024/01/02 10:49:42 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	memswap8(unsigned char *a, unsigned char *b)
{
	if (a == b)
		return ;
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

static void	memswap(unsigned char *a, unsigned char *b, size_t bytes)
{
	size_t	i;

	if (!a || !b)
		return ;
	i = 0;
	while (i < bytes)
	{
		memswap8(&a[i], &b[i]);
		i++;
	}
}

static size_t	vec_partition(t_vec *src, int low,
	int high, int (*f)(void *, void *))
{
	void	*pivot;
	int		i;
	int		j;

	pivot = vec_get(src, high);
	i = low - 1;
	j = low;
	while (j < high)
	{
		if (f(vec_get(src, j), pivot) <= 0)
		{
			i++;
			memswap(vec_get(src, i), vec_get(src, j), src->elem_size);
		}
		j++;
	}
	i++;
	memswap(vec_get(src, i), pivot, src->elem_size);
	return (i);
}

static void	vec_quicksort(t_vec *src, int low,
	int high, int (*f)(void *, void *))
{
	int	p;

	if (low >= high || low < 0)
		return ;
	p = vec_partition(src, low, high, f);
	vec_quicksort(src, low, p - 1, f);
	vec_quicksort(src, p + 1, high, f);
}

void	vec_sort(t_vec *src, int (*f)(void *, void *))
{
	if (!src || !src->memory)
		return ;
	vec_quicksort(src, 0, src->len - 1, f);
}
