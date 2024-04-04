/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd_us.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 09:10:29 by toramo            #+#    #+#             */
/*   Updated: 2023/11/06 17:05:50 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd_us(unsigned int nb, int fd)
{
	int		n;
	char	nbr[16];

	n = 1;
	nbr[0] = (nb % 10) + 48;
	while (nb / 10 != 0)
	{
		nb = nb / 10;
		nbr[n] = (nb % 10) + 48;
		n++;
	}
	n--;
	while (n >= 0)
	{
		write(fd, &nbr[n], 1);
		n--;
	}
}
