/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_write_funcs3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:02:47 by toramo            #+#    #+#             */
/*   Updated: 2023/11/08 12:02:49 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	printf_write_percentage(t_printf *tab)
{
	if (tab -> width != 0 && tab -> minus == 0)
		write_pad_chars(' ', (tab -> width - 1), tab);
	tab -> written += write(1, "%", 1);
	if (tab -> width != 0 && tab -> minus == 1)
		write_pad_chars(' ', (tab -> width - 1), tab);
}

void	printf_write_null(t_printf *tab)
{
	int	strl;

	strl = 6;
	if (tab -> dot && 6 > tab -> precision)
		strl = tab -> precision;
	if (tab -> width != 0 && tab -> minus == 0)
		write_pad_chars(' ', (tab -> width - strl), tab);
	tab -> written += write (1, "(null)", strl);
	if (tab -> width != 0 && tab -> minus == 1)
		write_pad_chars(' ', (tab -> width - strl), tab);
}

void	printf_write_int_us(t_printf *tab)
{
	char	pad;
	int		padsize;
	int		intlength;

	intlength = int_str_size_printf_us((unsigned long int)tab -> arg, tab);
	pad = 32;
	if (tab -> zero == 1 && tab -> precision == 0)
		pad = '0';
	if (intlength >= tab -> precision)
		padsize = tab -> width - intlength;
	else
		padsize = tab -> width - tab -> precision;
	if (tab -> minus == 0 && padsize > 0)
		write_pad_chars(pad, padsize, tab);
	if (tab -> precision > intlength)
		write_pad_chars('0', ((tab -> precision) - intlength), tab);
	if (!(tab -> dot == 1 && tab -> precision == 0
			&& (unsigned long int)tab -> arg == 0))
		ft_putnbr_fd_us((unsigned long int)tab -> arg, 1);
	tab -> written += intlength;
	if (tab -> minus == 1 && padsize > 0)
		write_pad_chars(' ', padsize, tab);
}

void	printf_write_hex(t_printf *tab)
{
	char			*str;
	unsigned int	i;
	int				padsize;
	char			pad;

	i = (unsigned long int)tab -> arg;
	str = ft_calloc(64, sizeof(char));
	if (!str)
		return ;
	pad = 32;
	if (tab -> zero == 1 && tab -> dot == 0)
		pad = '0';
	unsigned_to_hex_str(str, i, tab, 0);
	padsize = tab -> width - ft_hexlength(str, tab);
	if (tab -> alt && i != 0)
		padsize = padsize - 2;
	if (tab -> minus == 0 && padsize > 0 && pad == ' ')
		write_pad_chars(pad, padsize, tab);
	printf_write_hex2(tab, str, padsize, pad);
}

void	printf_write_hex2(t_printf *tab, char *str, int padsize, char pad)
{
	if (tab -> alt && (unsigned long int)tab -> arg != 0 && tab -> type == 'x')
		tab -> written += write(1, "0x", 2);
	if (tab -> alt && (unsigned long int)tab -> arg != 0 && tab -> type == 'X')
		tab -> written += write(1, "0X", 2);
	if (tab -> minus == 0 && padsize > 0 && pad == '0')
		write_pad_chars(pad, padsize, tab);
	if (tab -> precision > (int)ft_strlen(str))
		write_pad_chars('0', tab -> precision - ft_strlen(str), tab);
	tab -> written += write(1, str, ft_strlen(str));
	if (tab -> minus == 1 && padsize > 0)
		write_pad_chars(pad, padsize, tab);
	free(str);
}
