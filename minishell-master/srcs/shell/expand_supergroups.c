/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_supergroups.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:08:24 by toramo            #+#    #+#             */
/*   Updated: 2024/02/09 15:08:41 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_parentheses(char *cmd_line)
{
	size_t	i;
	size_t	open_parentheses;
	size_t	start;
	size_t	end;

	open_parentheses = 0;
	i = 0;
	while (cmd_line[i] && cmd_line[i] != '(')
		i++;
	open_parentheses++;
	start = i;
	while (cmd_line[i] && !(open_parentheses == 0
			&& cmd_line[i] == ')'))
	{
		i++;
		if (cmd_line[i] == '(')
			open_parentheses++;
		if (cmd_line[i] == ')')
			open_parentheses--;
	}
	end = i;
	ft_memmove(&cmd_line[start], &cmd_line[start + 1],
		ft_strlen(&cmd_line[start + 1]));
	cmd_line[end - 1] = 0;
}
