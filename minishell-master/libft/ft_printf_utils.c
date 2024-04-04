/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:54:16 by toramo            #+#    #+#             */
/*   Updated: 2023/11/08 11:54:21 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	update_tab(char *str, t_printf *tab, va_list arg_ptr)
{
	int		i;

	i = 1;
	reset_printf_tab(tab);
	if (!ft_strchr(&str[1], '%'))
		tab -> arg = va_arg(arg_ptr, void *);
	while ((str[i] == '#' || str[i] == '0' || str[i] == '-'
			|| str[i] == '+' || str[i] == 32) && str[i] != 0)
		i++;
	printf_assign_flags(str, tab, i);
	tab -> width = ft_atoi(&str[i]);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == '.')
	{
		tab -> dot = 1;
		i++;
		tab -> precision = ft_atoi(&str[i]);
		while (ft_isdigit(str[i]))
			i++;
	}
	tab -> type = str[i];
}

t_printf	*ft_init_printf_tab(void)
{
	t_printf	*tab;

	tab = malloc(sizeof(t_printf));
	if (!tab)
		return (0);
	tab -> alt = 0;
	tab -> arg = 0;
	tab -> zero = 0;
	tab -> minus = 0;
	tab -> plus = 0;
	tab -> space = 0;
	tab -> dot = 0;
	tab -> width = 0;
	tab -> precision = 0;
	tab -> type = 0;
	tab -> written = 0;
	return (tab);
}

int	free_printf_mem(t_printf *tab, char **strs)
{
	int	i;

	i = 0;
	if (!tab && strs)
	{
		while (strs[i])
		{
			free(strs[i]);
			i++;
		}
		free(strs);
		return (-1);
	}
	if (!strs && tab)
		free(tab);
	return (-1);
}

void	printf_assign_flags(char *str, t_printf *tab, int i)
{
	if (ft_strchr(str, '#'))
		tab -> alt = 1;
	if (ft_memchr(str, '0', i))
		tab -> zero = 1;
	if (ft_strchr(str, '-'))
		tab -> minus = 1;
	if (ft_strchr(str, '+'))
		tab -> plus = 1;
	if (ft_strchr(str, 32))
		tab -> space = 1;
}

void	conversion(char *str, t_printf *tab, va_list arg_ptr)
{
	update_tab(str, tab, arg_ptr);
	if (tab -> arg == 0 && tab -> type == 's')
	{
		printf_write_null(tab);
		return ;
	}
	if (tab -> type == '%')
		printf_write_percentage(tab);
	if (tab -> type == 'c')
		printf_write_char(tab);
	if (tab -> type == 's')
		printf_write_string(tab);
	if (tab -> type == 'p')
		printf_write_pointer(tab);
	if (tab -> type == 'd')
		printf_write_int(tab);
	if (tab -> type == 'i')
		printf_write_int(tab);
	if (tab -> type == 'u')
		printf_write_int_us(tab);
	if (tab -> type == 'x')
		printf_write_hex(tab);
	if (tab -> type == 'X')
		printf_write_hex(tab);
}
