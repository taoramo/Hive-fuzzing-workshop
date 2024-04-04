/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_write_funcs.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:01:49 by toramo            #+#    #+#             */
/*   Updated: 2023/11/08 12:01:52 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	write_pad_chars(char c, int i, t_printf *tab)
{
	while (i > 0)
	{
		tab -> written += write(1, &c, 1);
		i--;
	}
}

void	printf_write_char(t_printf *tab)
{
	if (tab -> width != 0 && tab -> minus == 0)
		write_pad_chars(' ', (tab -> width - 1), tab);
	tab -> written += write(1, &tab -> arg, 1);
	if (tab -> width != 0 && tab -> minus == 1)
		write_pad_chars(' ', (tab -> width - 1), tab);
}

void	printf_write_string(t_printf *tab)
{
	int	strl;

	strl = ft_strlen((char *)tab -> arg);
	if (tab -> dot && (int)ft_strlen((char *)tab -> arg) > tab -> precision)
		strl = tab -> precision;
	if (tab -> width != 0 && tab -> minus == 0)
		write_pad_chars(' ', (tab -> width - strl), tab);
	tab -> written += write (1, (char *)tab -> arg, strl);
	if (tab -> width != 0 && tab -> minus == 1)
		write_pad_chars(' ', (tab -> width - strl), tab);
}

void	printf_write_int(t_printf *tab)
{
	char	pad;
	int		padsize;
	int		intlength;

	intlength = int_str_size_printf((long)tab -> arg, tab);
	pad = 32;
	if (tab -> zero == 1 && tab -> dot == 0)
		pad = '0';
	if (intlength >= tab -> precision)
		padsize = tab -> width - intlength;
	else
		padsize = tab -> width - tab -> precision;
	if (tab -> dot == 1 && tab -> precision == 0 && (long)tab -> arg == 0)
		padsize++;
	if ((long)tab -> arg < 0 || ((long)tab -> arg >= 0 && tab -> plus))
		padsize--;
	if (tab -> space == 1 && (long)tab -> arg >= 0)
		padsize--;
	if (tab -> minus == 0 && padsize > 0 && pad == ' ')
		write_pad_chars(pad, padsize, tab);
	printf_write_int2(tab, pad, padsize, intlength);
}

void	printf_write_int2(t_printf *tab, char pad, int padsize, int intlength)
{
	if (tab -> space == 1 && (long)tab -> arg >= 0)
		tab -> written += write(1, " ", 1);
	if ((long)tab -> arg >= 0 && tab -> plus)
		tab -> written += write(1, "+", 1);
	if ((long)tab -> arg < 0 && (long)tab -> arg > -2147483648)
		tab -> written += write(1, "-", 1);
	if (tab -> minus == 0 && padsize > 0 && pad == '0')
		write_pad_chars(pad, padsize, tab);
	if (tab -> precision > intlength)
		write_pad_chars('0', ((tab -> precision) - intlength), tab);
	if (!((long)tab -> arg == 0 && tab -> dot == 1 && tab -> precision == 0))
		ft_putnbr_fd(ft_abs((long)tab -> arg), 1);
	if (tab -> minus == 1 && padsize > 0)
		write_pad_chars(' ', padsize, tab);
}
