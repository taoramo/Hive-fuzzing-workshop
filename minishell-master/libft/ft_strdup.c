/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:16:58 by toramo            #+#    #+#             */
/*   Updated: 2023/10/30 10:16:59 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*cpy;

	cpy = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (cpy == 0)
		return (0);
	ft_strlcpy(cpy, src, (ft_strlen(src) + 1));
	return (cpy);
}
