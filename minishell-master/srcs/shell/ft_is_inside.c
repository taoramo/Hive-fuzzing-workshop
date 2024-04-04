/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_inside.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:08:48 by toramo            #+#    #+#             */
/*   Updated: 2024/02/09 15:08:53 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_inside_parenth(const char *line, int i, int open_char)
{
	int	j;
	int	is_inside;
	int	closed_char;

	j = 0;
	is_inside = 0;
	if (open_char == '(')
		closed_char = ')';
	if (open_char == '{')
		closed_char = '}';
	if (open_char == '[')
		closed_char = ']';
	while (line[j] && j < i)
	{
		if (line[j] == open_char)
			is_inside += 1;
		if (line[j] == closed_char)
			is_inside -= 1;
		j++;
	}
	return (is_inside);
}

int	ft_is_inside(const char *line, int i, int open_char)
{
	int	j;
	int	is_inside;

	if (open_char == '(' || open_char == '[' || open_char == '{')
		return (is_inside_parenth(line, i, open_char));
	j = 0;
	is_inside = 0;
	while (line[j] && j < i)
	{
		if (line[j] == open_char && is_inside == 0)
			is_inside = 1;
		else if (line[j] == open_char && is_inside == 1)
			is_inside = 0;
		j++;
	}
	return (is_inside);
}
