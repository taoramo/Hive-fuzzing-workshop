/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipelines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:48:20 by toramo            #+#    #+#             */
/*   Updated: 2024/02/15 10:26:13 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	next_cmd_line(t_vec *cmd_lines, size_t *i, int *last_return)
{
	char	*curr_cmd_line;
	char	**strs;

	strs = (char **)cmd_lines->memory;
	if (*last_return != 0)
	{
		curr_cmd_line = strs[*i];
		while (*i < cmd_lines->len
			&& ft_strncmp(curr_cmd_line, "|| ", 3))
		{
			*i = *i + 1;
			curr_cmd_line = strs[*i];
		}
	}
	else
	{
		curr_cmd_line = strs[*i];
		while (*i < cmd_lines->len
			&& ft_strncmp(curr_cmd_line, "&& ", 3))
		{
			*i = *i + 1;
			curr_cmd_line = strs[*i];
		}
	}
}

int	handle_parentheses(char *cmd_line, int *last_return, t_vec *env)
{
	remove_parentheses(cmd_line);
	if (parse_line(cmd_line, last_return, env) < 0)
		return (-1);
	else
		return (0);
}

int	next_cmd_line_action(char *cmd_line, t_envinfo envinfo)
{
	if (*cmd_line == '(')
	{
		if (handle_parentheses(cmd_line, envinfo.last_return, envinfo.env) < 0)
			return (-1);
	}
	else if (check_cmd_line_syntax(cmd_line) < 0)
		return (-1);
	else
	{
		*envinfo.last_return = run_command(cmd_line, envinfo);
	}
	return (0);
}

int	check_andor_syntax(char **strs, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < len)
	{
		j = 0;
		if (strs[i][0] == '&' || strs[i][0] == '|')
		{
			j = j + 2;
			if (strs[i][2] == '|')
				return (ft_error("syntax error near unexpected token `|’"));
			if (strs[i][2] == '&')
				return (ft_error("syntax error near unexpected token `&’"));
			while (ft_isspace(strs[i][j]))
				j++;
			if (strs[i][j] == '|')
				return (ft_error("syntax error near unexpected token `|’"));
			if (strs[i][j] == '&')
				return (ft_error("syntax error near unexpected token `&’"));
		}
		i++;
	}
	return (1);
}

int	redirect_check_error(char c)
{
	write(2, "minishell: syntax error near unexpected token `", 47);
	write(2, &c, 1);
	write(2, "'\n", 2);
	return (-1);
}

int	check_redirect_cmdline(char *cmd_line)
{
	int		i;
	char	c;

	i = 0;
	while (cmd_line[i])
	{
		if (cmd_line[i] == '<' || cmd_line[i] == '>')
		{
			c = cmd_line[i];
			if ((c == '<' && cmd_line[i + 1] == '>') || (c == '>' && cmd_line[i + 1] == '<'))
				return (redirect_check_error(c));
			if (cmd_line[i] && cmd_line[i + 1] == cmd_line[i])
				i++;
			i++;
			while (ft_isspace(cmd_line[i]))
				i++;
			if (!cmd_line[i] || cmd_line[i] == '|' || cmd_line[i] == '&' || cmd_line[i] == '(' || cmd_line[i] == ')')
				return (redirect_check_error(c));
		}
		i++;
	}
	return (1);
}

int	check_redirect(t_vec *cmd_lines)
{
	size_t	i;

	i = 0;
	while (i < cmd_lines->len)
	{
		if (check_redirect_cmdline(*(char **)vec_get(cmd_lines, i)) < 0)
			return (-1);
		i++;
	}
	return (0);
}

int	handle_pipelines(t_vec *cmd_lines, int *last_return, t_vec *env)
{
	size_t		i;
	size_t		j;
	char		**strs;
	t_vec		heredoc_fd_list;
	t_envinfo	envinfo;

	i = 0;
	strs = (char **)cmd_lines->memory;
	if (check_andor_syntax(strs, cmd_lines->len) < 0 || check_parenth_syntax(cmd_lines) < 0 || check_redirect(cmd_lines) < 0)
		return (handle_pipelines_error(cmd_lines));
	if (vec_new(&heredoc_fd_list, cmd_lines->len, sizeof(t_vec)) == -1)
		return (-1);
	if (get_heredocs(&heredoc_fd_list, cmd_lines) < 0)
		return (handle_pipelines_error(cmd_lines));
	envinfo.env = env;
	envinfo.last_return = last_return;
	while (i < cmd_lines->len && *last_return != INT_MIN)
	{
		envinfo.heredoc_fds = *(t_vec *)vec_get(&heredoc_fd_list, i);
		j = 0;
		if (strs[i][0] == '&' || strs[i][0] == '|')
			j = j + 2;
		while (ft_isspace(strs[i][j]))
			j++;
		if (next_cmd_line_action(&strs[i][j], envinfo) < 0)
			return (handle_pipelines_error(cmd_lines));
		i++;
		next_cmd_line(cmd_lines, &i, envinfo.last_return);
	}
	free_split_vec(cmd_lines);
	return (*envinfo.last_return);
}
