/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:52:17 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/15 13:46:46 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_outer_quotes(char *str)
{
	char	*new_str;
	int		i;
	int		len;

	new_str = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (new_str == 0)
		return (0);
	i = 0;
	while (*str != 0)
	{
		if (*str == '\"' || *str == '\'')
		{
			len = quote_length(str);
			ft_memcpy(&new_str[i], str + 1, len - 1);
			i += len - 1;
			str += len;
		}
		else
		{
			new_str[i] = *str;
			i++;
		}
		str++;
	}
	return (new_str);
}

int	remove_quotes(t_vec *argv)
{
	char	**str_ptr;
	char	*new_str;
	size_t	i;

	i = 0;
	while(i < argv->len)
	{
		str_ptr = (char **)vec_get(argv, i);
		if (ft_strchr(*str_ptr, '\"') || ft_strchr(*str_ptr, '\''))
		{
			new_str = remove_outer_quotes(*str_ptr);
			free(*str_ptr);
			*str_ptr = new_str;
		}
		i++;
	}
	return (1);
}
