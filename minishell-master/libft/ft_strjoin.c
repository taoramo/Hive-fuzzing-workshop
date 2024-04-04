/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:17:39 by toramo            #+#    #+#             */
/*   Updated: 2023/10/30 10:17:40 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str;

	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str || !s1 || !s2)
		return (0);
	if (s1[0] == 0 && s2[0] == 0)
	{
		str[0] = 0;
		return (str);
	}
	ft_strlcpy(str, s1, ft_strlen(s1) + 1);
	if (s2[0] != 0)
		ft_strlcat(str, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	return (str);
}
