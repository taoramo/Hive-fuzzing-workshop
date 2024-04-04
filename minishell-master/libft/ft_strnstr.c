/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:19:24 by toramo            #+#    #+#             */
/*   Updated: 2023/10/31 11:34:10 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	l;
	size_t	i;

	i = 0;
	l = ft_strlen(to_find);
	if (str == 0 && len > 0)
		ft_strlen(&str[0]);
	if (to_find[0] == 0)
		return ((char *)str);
	while (i + l <= len && str[i] != 0)
	{
		if (ft_strncmp(to_find, &str[i], l) == 0)
			return ((char *)&str[i]);
		i++;
	}
	return (0);
}
