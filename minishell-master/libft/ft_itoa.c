/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 09:26:40 by toramo            #+#    #+#             */
/*   Updated: 2023/10/31 12:41:05 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	int_str_size(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (2);
	if (n < 0)
	{
		i++;
		n = n * -1;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	i++;
	return (i);
}

char	*ft_itoa_array(int n, char *result, int i, int j)
{
	char	*str;

	str = malloc(sizeof(char) * int_str_size(n));
	if (!str)
	{
		free(result);
		return (0);
	}
	if (n < 0)
	{
		result[j++] = '-';
		n = n * -1;
	}
	while (n != 0)
	{
		str[i++] = n % 10 + 48;
		n = n / 10;
	}
	i--;
	while (i + 1)
		result[j++] = str[i--];
	result[j] = 0;
	free (str);
	return (result);
}

char	*ft_itoa(int n)
{
	char	*result;

	if (n == -2147483648)
		result = malloc(sizeof(char) * 12);
	else
		result = malloc(sizeof(char) * int_str_size(n));
	if (result != 0)
	{
		if (n == 0)
		{
			ft_strlcpy(result, "0", 2);
			return (result);
		}
		if (n == -2147483648)
		{
			ft_strlcpy(result, "-2147483648", 12);
			return (result);
		}
		result = ft_itoa_array(n, result, 0, 0);
	}
	return (result);
}
