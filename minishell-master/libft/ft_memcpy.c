/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 09:36:36 by toramo            #+#    #+#             */
/*   Updated: 2023/10/30 09:37:31 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *) dst;
	s = (const unsigned char *) src;
	if (!dst && !src)
		return (dst);
	while (n)
	{
		*d = *s;
		d++;
		s++;
		n--;
	}
	return (dst);
}
