/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:08:10 by toramo            #+#    #+#             */
/*   Updated: 2024/02/09 15:08:13 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error(char *str)
{
	if (ft_strlen(str))
	{
		ft_putstr_fd(str, 2);
		write(2, "\n", 1);
		rl_on_new_line();
	}
	return (-1);
}

int	cmd_line_error(t_vec *cmd_lines)
{
	free_split_vec(cmd_lines);
	return (ft_error("error allocating memory"));
}

int	minishell_error(char *str, char *message)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(message, 2);
	ft_putchar_fd('\n', 2);
	return (-1);
}

char	*cd_error(char *str)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(str, 2);
	write(2, "\n", 1);
	return (0);
}

int	handle_pipelines_error(t_vec *cmd_lines)
{
	free_split_vec(cmd_lines);
	return (-1);
}
