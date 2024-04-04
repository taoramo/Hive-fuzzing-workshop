/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_printf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:26:33 by toramo            #+#    #+#             */
/*   Updated: 2023/11/08 11:51:05 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen_percentage(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != 0 && s[i] != '%')
		i++;
	return (i);
}

int	ft_strlen_format(const char *s, int i, int j)
{
	while (s[i] == '#' || s[i] == '0'
		|| s[i] == '-' || s[i] == 32 || s[i] == '+')
	{
		j++;
		i++;
	}
	while (ft_isdigit(s[i]))
	{
		j++;
		i++;
	}
	if (s[i] == '.')
	{
		i++;
		j++;
		while (ft_isdigit(s[i]))
		{
			j++;
			i++;
		}
	}
	if (s[i] == 'c' || s[i] == 's' || s[i] == 'p' || s[i] == 'd' || s[i]
		=='i' || s[i] == 'u' || s[i] == 'x' || s[i] == 'X' || s[i] == '%')
		j++;
	return (j);
}

int	ft_strlen_printf(const char *s)
{
	if (s[0] != '%')
		return (ft_strlen_percentage(s));
	else
		return (ft_strlen_format(s, 1, 1));
}

char	**ft_split_printf(const char *s)
{
	int		i;
	int		j;
	char	**strs;

	j = 0;
	i = 0;
	strs = (char **)malloc(sizeof(char *) * (count_words_printf(s) + 1));
	if (strs == 0)
		return (0);
	while (i < count_words_printf(s))
	{
		strs[i] = malloc(sizeof(char) * (ft_strlen_printf(&s[j]) + 1));
		if (strs[i] == 0)
			return (ft_free_arr_printf(strs, i));
		ft_strlcpy(strs[i], &s[j], (ft_strlen_printf(&s[j]) + 1));
		j = j + ft_strlen_printf(&s[j]);
		i++;
	}
	strs[i] = 0;
	return (strs);
}
