/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 08:56:23 by toramo            #+#    #+#             */
/*   Updated: 2023/11/10 12:22:33 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	int			strlen;
	char		buf[BUFFER_SIZE];
	static char	backup[FD_MAX][BUFFER_SIZE + 4];
	int			*in_buffer;
	char		*str;

	if (fd > FD_MAX || fd < 0)
		return (0);
	str = 0;
	strlen = 0;
	in_buffer = (int *)&backup[fd][BUFFER_SIZE];
	*in_buffer = *in_buffer - !(*in_buffer);
	while (*in_buffer != 0)
	{
		str = cp_and_move(str, &strlen, in_buffer, backup[fd]);
		if (!str && *in_buffer != -1)
			return (0);
		if (*in_buffer != -1 && ft_strlen_gnl(str, strlen, 0))
			return (gnl_insert_null(str, strlen));
		*in_buffer = read(fd, buf, BUFFER_SIZE);
		if (*in_buffer == -1)
			return (free_if_exists((str), in_buffer));
		ft_memmove_gnl(backup[fd], buf, BUFFER_SIZE);
	}
	return (gnl_insert_null(str, strlen));
}
