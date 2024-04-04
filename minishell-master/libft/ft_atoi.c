/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 09:22:02 by toramo            #+#    #+#             */
/*   Updated: 2023/10/30 09:22:07 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_to_int(const char *str)
{
	int		i;
	long	result;

	result = 0;
	i = 0;
	while (str[i] != 0 && str[i] > 47 && str[i] < 58)
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	if (result > 2147483647 || result < -2147483648)
		return (0);
	return ((int)result);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	m;

	i = 0;
	m = 1;
	while (((str[i] == 32) || (str[i] > 8 && str[i] < 14)) && str[i] != 0)
	{
		i++;
	}
	if ((str[i] == 43 || str[i] == 45) && str[i] != 0)
	{
		if (str[i] == 45)
			m = -1;
		i++;
	}
	return (ft_str_to_int(&str[i]) * m);
}
