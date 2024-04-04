/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:46:41 by toramo            #+#    #+#             */
/*   Updated: 2023/11/07 09:38:50 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *s, ...)
{
	int			i;
	char		**strs;
	va_list		arg_ptr;
	t_printf	*tab;

	i = 0;
	va_start(arg_ptr, s);
	strs = ft_split_printf(s);
	tab = ft_init_printf_tab();
	if (!strs || !tab)
		return (free_printf_mem(tab, strs));
	while (strs[i])
	{
		if (strs[i][0] == '%')
			conversion(strs[i], tab, arg_ptr);
		else
			tab -> written += write(1, strs[i], ft_strlen(strs[i]));
		i++;
	}
	ft_free_arr(strs, i);
	va_end(arg_ptr);
	i = tab -> written;
	free(tab);
	return (i);
}
