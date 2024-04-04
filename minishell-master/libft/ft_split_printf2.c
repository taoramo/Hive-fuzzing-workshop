/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_printf2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:49:01 by toramo            #+#    #+#             */
/*   Updated: 2023/11/08 11:55:50 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_words_printf(const char *s)
{
	int	i;
	int	c;

	c = 0;
	i = 0;
	while (s[i] != 0)
	{
		c++;
		i += ft_strlen_printf(&s[i]);
	}
	return (c);
}

char	**ft_free_arr_printf(char **strs, int i)
{
	while (i >= 0)
	{
		free(strs[i]);
		i--;
	}
	free(strs);
	return (0);
}
