/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:20:08 by toramo            #+#    #+#             */
/*   Updated: 2023/10/30 10:20:12 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;

	if (len == 0 || start >= ft_strlen(s))
	{
		str = malloc(sizeof(char));
		if (!str)
			return (0);
		str[0] = 0;
		return (str);
	}
	if (ft_strlen(&s[start]) > len)
	{
		str = malloc(sizeof(char) * (len + 1));
		if (!str)
			return (0);
		ft_strlcpy(str, &s[start], (len + 1));
	}
	else
	{
		str = malloc(sizeof(char) * (ft_strlen(&s[start]) + 1));
		if (!str)
			return (0);
		ft_strlcpy(str, &s[start], (ft_strlen(&s[start]) + 1));
	}
	return (str);
}
