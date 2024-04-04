/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parentheses.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:16:56 by toramo            #+#    #+#             */
/*   Updated: 2024/02/09 15:16:59 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	next_start(const char *line, int i)
{
	if (i == 0)
		return (0);
	while (line[i])
	{
		if (!ft_strncmp(&line[i], "&&", 2) || !ft_strncmp(&line[i], "||", 2))
		{
			if (!ft_is_inside(line, i, '"') && !ft_is_inside(line, i, 39))
				break ;
		}
		i++;
	}
	return (i);
}

int	length_next_in_parenth(const char *line, int index)
{
	int	i;
	int	open_parentheses;

	i = 0;
	open_parentheses = 0;
	while (line[index + i])
	{
		if (open_parentheses == 0 && line[index + i - 1] == ')'
			&& !ft_is_inside(line, i, '"') && !ft_is_inside(line, i, 39))
			break ;
		if (line[index + i] == '('
			&& !ft_is_inside(line, index + i, 39)
			&& !ft_is_inside(line, index + i, '"'))
			open_parentheses++;
		if (line[index + i] == ')'
			&& open_parentheses
			&& !ft_is_inside(line, index + i, 39)
			&& !ft_is_inside(line, index + i, '"'))
			open_parentheses--;
		i++;
	}
	return (i);
}

int	length_next_outside_parenth(const char *line, int index)
{
	int	i;

	i = 0;
	while (line[index + i])
	{
		if (!ft_strncmp(&line[index + i], "&&", 2)
			|| !ft_strncmp(&line[index + i], "||", 2))
		{
			if (!ft_is_inside(line, index + i, '"')
				&& !ft_is_inside(line, index + i, 39))
				break ;
		}
		i++;
	}
	return (i);
}

int	next_length(const char *line, int index)
{
	int	i;

	i = 0;
	if (line[index] == 0)
		return (0);
	if (index == 0)
	{
		if (line[0] == '(')
			return (length_next_in_parenth(line, index));
		else
			return (length_next_outside_parenth(line, index));
	}
	else
	{
		while (ft_isspace(line[index + i]))
			i++;
		i = i + 2;
		while (ft_isspace(line[index + i]))
			i++;
		if (line[index + i] == '(' && !ft_is_inside(line, index + i, 39)
			&& !ft_is_inside(line, index + i, '"'))
			return (length_next_in_parenth(line, index + i) + i);
		else
			return (length_next_outside_parenth(line, index + i) + i);
	}
}

int	make_cmd_line_groups(t_vec *cmd_lines,
	const char *line, int *last_return, t_vec *env)
{
	int			i;
	int			start;
	int			length;
	char		*current;

	i = 0;
	while (line[i])
	{
		start = next_start(line, i);
		length = next_length(line, start);
		current = ft_substr(line, start, length);
		if (!current)
		{
			free_split_vec(env);
			return (cmd_line_error(cmd_lines));
		}
		if (vec_push(cmd_lines, &current) < 0)
		{
			free_split_vec(env);
			return (cmd_line_error(cmd_lines));
		}
		i = start + length;
	}
	return (handle_pipelines(cmd_lines, last_return, env));
}
