/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:53:56 by toramo            #+#    #+#             */
/*   Updated: 2023/11/08 11:54:01 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	int_str_size_printf_us(unsigned int n, t_printf *tab)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
	{
		if (tab -> dot == 1 && tab -> precision == 0)
			return (0);
		else
			return (1);
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

int	int_str_size_printf(int n, t_printf *tab)
{
	int	i;

	i = 0;
	if (n == 0)
	{
		if (!(tab -> dot == 1 && tab -> precision == 0))
			tab -> written++;
		return (1);
	}
	if ((int)n == -2147483648)
	{
		tab -> written += 11;
		return (10);
	}
	if (n < 0)
	{
		n = n * -1;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	tab -> written += i;
	return (i);
}

void	reset_printf_tab(t_printf *tab)
{
	tab -> alt = 0;
	tab -> zero = 0;
	tab -> minus = 0;
	tab -> plus = 0;
	tab -> space = 0;
	tab -> dot = 0;
	tab -> width = 0;
	tab -> precision = 0;
	tab -> type = 0;
}
