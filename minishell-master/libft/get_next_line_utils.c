/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 08:56:41 by toramo            #+#    #+#             */
/*   Updated: 2023/11/10 12:22:30 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove_gnl(void *dst, const void *src, size_t len)
{
	unsigned char	*tdst;
	unsigned char	*tsrc;

	tdst = (unsigned char *)dst;
	tsrc = (unsigned char *)src;
	if (dst < src)
	{
		while (len)
		{
			*tdst = *tsrc;
			tdst++;
			tsrc++;
			len--;
		}
		return (dst);
	}
	if (dst > src)
		while (len--)
			tdst[len] = tsrc[len];
	return (dst);
}

int	ft_strlen_gnl(char *str, int len, int flag)
{
	int	i;

	i = 0;
	if (flag == 0)
	{
		while (i < len)
		{
			if (str[i] == '\n')
				return (1);
			i++;
		}
		return (0);
	}
	else
	{
		while (str[i] != '\n' && i < len)
			i++;
		if (str[i] == '\n' && i < len)
			i++;
		return (i);
	}
}

char	*free_if_exists(char *str, int *in_buffer)
{
	if (in_buffer)
		*in_buffer = 0;
	if (str)
		free(str);
	return (0);
}

char	*cp_and_move(char *str, int *strlen, int *in_buffer, char *buf)
{
	char	*temp;
	int		to_write;

	if (*in_buffer < 0)
		return (str);
	to_write = ft_strlen_gnl(buf, *in_buffer, 1);
	temp = str;
	str = malloc(sizeof(char) * (*strlen + to_write));
	if (!str)
		return (free_if_exists(temp, in_buffer));
	ft_memmove_gnl(str, temp, *strlen);
	free_if_exists(temp, 0);
	ft_memmove_gnl(&str[*strlen], buf, to_write);
	*strlen += to_write;
	if (to_write < *in_buffer)
	{
		ft_memmove_gnl(buf, &buf[to_write], *in_buffer - to_write);
		*in_buffer = *in_buffer - to_write;
		return (str);
	}
	else
	{
		*in_buffer = 0;
		return (str);
	}
}

char	*gnl_insert_null(char *str, int strlen)
{
	char	*temp;

	if (strlen == 0)
		return (0);
	temp = str;
	str = malloc(sizeof(char) * (strlen + 1));
	if (!str)
	{
		free(temp);
		return (0);
	}
	ft_memmove_gnl(str, temp, strlen);
	free(temp);
	str[strlen] = 0;
	return (str);
}
