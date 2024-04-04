/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 09:48:48 by toramo            #+#    #+#             */
/*   Updated: 2023/10/31 12:59:15 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_words(const char *str, char sep)
{
	int	i;
	int	c;

	c = 0;
	i = 0;
	while (str[i] != 0)
	{
		while (str[i] == sep)
		{
			i++;
		}
		if (str[i] != 0)
			c++;
		while ((str[i] != sep) && str[i] != 0)
		{
			i++;
		}
	}
	return (c);
}

int	ft_strlen_member(const char *str, char sep)
{
	int	n;

	n = 0;
	if (str[0] != 0)
	{
		while (str[n] != 0 && str[n] != sep)
		{
			n++;
		}
	}
	return (n);
}

char	**ft_free_arr(char **strs, int i)
{
	while (i >= 0)
	{
		free(strs[i]);
		i--;
	}
	free(strs);
	return (0);
}

char	**ft_split(const char *s, char c)
{
	int		i;
	int		j;
	char	**strs;

	j = 0;
	i = 0;
	strs = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (strs == 0)
		return (0);
	while (i < count_words(s, c))
	{
		if (s[j] == c)
			j++;
		else
		{
			strs[i] = malloc(sizeof(char) * (ft_strlen_member(&s[j], c) + 1));
			if (strs[i] == 0)
				return (ft_free_arr(strs, i));
			ft_strlcpy(strs[i], &s[j], (ft_strlen_member(&s[j], c) + 1));
			j = j + ft_strlen_member(&s[j], c);
			i++;
		}
	}
	strs[i] = 0;
	return (strs);
}
