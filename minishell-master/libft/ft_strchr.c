/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:16:49 by toramo            #+#    #+#             */
/*   Updated: 2023/10/30 10:16:50 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	a;

	a = (unsigned char)c;
	if (a == '\0' && *s == 0)
		return ((char *)s);
	while (*s)
	{
		if (*s == a)
			return ((char *)s);
		s++;
	}
	if (*s == 0 && a == '\0')
		return ((char *)s);
	return (0);
}
