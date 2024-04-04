/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:09:12 by toramo            #+#    #+#             */
/*   Updated: 2024/02/15 12:39:11 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_line(const char *line, int *last_return, t_vec *env)
{
	t_vec	cmd_lines;

	if (check_parenthesis_count(line) < 0 || check_open_quotes(line) < 0)
	{
		*last_return = 1;
		return (-1);
	}
	if (vec_new(&cmd_lines, 16, sizeof(char *)) < 0)
	{
		free_split_vec(env);
		return (ft_error("malloc"));
	}
	if (make_cmd_line_groups(&cmd_lines, line, last_return, env) == -1)
	{
		*last_return = 1;
		return (-1);
	}
	return (1);
}

int	copy_env(t_vec *env, char **environ)
{
	char		*temp;
	int			i;

	i = 0;
	if (vec_new(env, 64, sizeof(char *)) < 0)
		return (-1);
	while (environ[i])
	{
		temp = ft_strdup(environ[i]);
		if (!temp)
			return (free_split_vec(env));
		if (vec_push(env, &temp) < 0)
			return (free_split_vec(env));
		i++;
	}
	return (1);
}

int	interactive(int *last_return, t_vec *env)
{
	char	*line;

	using_history();
	read_history(0);
	*last_return = 0;
	while (*last_return != INT_MIN)
	{
		signal_interactive();
		line = readline("minishell> ");
		if (line && ft_strlen(line) > 0)
		{
			signal_non_interactive();
			add_history(line);
			write_history(0);
			parse_line(line, last_return, env);
		}
		else if (!line)
			break ;
		free(line);
	}
	write(2, "exit\n", 5);
	toggle_carret(1);
	clear_history();
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int		last_return;
	t_vec	env;

	if (copy_env(&env, envp) < 0)
	{
		ft_error("error allocating memory\n");
		return (-1);
	}
	last_return = 0;
	if (argc == 3 && !ft_strncmp(argv[1], "-c", 3))
		parse_line(argv[2], &last_return, &env);
	if (argc == 1)
		interactive(&last_return, &env);
	free_split_vec(&env);
	if (last_return != INT_MIN)
		return (last_return);
	else
		return (0);
}
