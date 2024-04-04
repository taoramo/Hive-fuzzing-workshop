/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_write_funcs2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:02:20 by toramo            #+#    #+#             */
/*   Updated: 2023/11/08 12:02:23 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	pointer_to_hex_str(char *str, unsigned long int n)
{
	int	temp[32];
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (n || i == 0)
	{
		temp[i] = n % 16;
		n = n / 16;
		i++;
	}
	i--;
	while (i > -1)
	{
		if (temp[i] < 10)
			str[j] = temp[i] + 48;
		else
			str[j] = temp[i] + 87;
		i--;
		j++;
	}
	str[j] = 0;
}

void	unsigned_to_hex_str(char *str, unsigned int n, t_printf *tab, int i)
{
	int	temp[16];
	int	j;

	j = 0;
	if (tab -> dot == 1 && tab -> precision == 0 && n == 0)
		return ;
	while (n || i == 0)
	{
		temp[i] = n % 16;
		n = n / 16;
		i++;
	}
	i--;
	while (i > -1)
	{
		if (temp[i] < 10)
			str[j] = temp[i] + 48;
		else
			str[j] = temp[i] + 87 + tab -> type - 120;
		i--;
		j++;
	}
	str[j] = 0;
}

void	printf_write_pointer(t_printf *tab)
{
	char				*str;
	unsigned long int	i;
	int					padsize;

	i = (unsigned long int)tab -> arg;
	str = malloc(sizeof(char) * 64);
	if (!str)
		return ;
	pointer_to_hex_str(str, i);
	if (tab -> precision > ft_hexlength(str, tab))
		padsize = tab -> width - tab -> precision - 2;
	else
		padsize = tab -> width - ft_hexlength(str, tab) - 2;
	if (tab -> minus == 0)
		write_pad_chars(' ', padsize, tab);
	tab -> written += write(1, "0x", 2);
	if (tab -> precision > (int)ft_strlen(str))
		write_pad_chars('0', tab -> precision - ft_strlen(str), tab);
	tab -> written += write(1, str, ft_strlen(str));
	if (tab -> minus == 1)
		write_pad_chars(' ', padsize, tab);
	free(str);
}

int	ft_hexlength(char *str, t_printf *tab)
{
	if ((int)ft_strlen(str) >= tab -> precision)
		return (ft_strlen(str));
	else
		return (tab -> precision);
}
