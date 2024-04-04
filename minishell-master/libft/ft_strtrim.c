/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:19:52 by toramo            #+#    #+#             */
/*   Updated: 2023/10/31 09:04:08 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_set_member(char c, const char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*empty_string(void)
{
	char	*empty;

	empty = malloc(sizeof(char));
	if (!empty)
		return (0);
	ft_strlcpy(empty, "", 1);
	return (empty);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	const char	*start;
	const char	*end;
	char		*str;

	start = s1;
	end = s1 + ft_strlen(s1);
	while (*start != 0 && ft_is_set_member(*start, set))
		start++;
	while (end >= start && (ft_is_set_member(*end, set) || *end == 0))
		end--;
	if (start <= end)
	{
		str = malloc((end - start + 2) * sizeof(char));
		if (!str)
			return (0);
		ft_strlcpy(str, start, (end - start + 2));
	}
	else
		str = empty_string();
	return (str);
}
