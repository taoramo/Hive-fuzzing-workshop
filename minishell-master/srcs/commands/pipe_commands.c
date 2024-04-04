/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:15:37 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/15 10:18:19 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int	run_single_pipe_command(t_command *command, int pipe_fds[], int pipe2_fds[], int pos)
{
	int	process_id;

	process_id = fork();
	if (process_id < 0)
	{
		perror("fork failed");
		return (-1);
	}
	else if (process_id == 0)
		handle_child(command, pipe_fds, pipe2_fds, pos);
	else
		handle_parent(pos, pipe_fds, pipe2_fds);
	return (process_id);
}

int first_pipe_commmand(t_pipe *pipeinfo, int i)
{
	t_command	command;
	int			ret;
	
	ret = prepare_pipe_command(&command, pipeinfo, i);
	if (ret != 0)
	{
		handle_parent(0, pipeinfo->pipe_fds, 0);
		return (ret);
	}
	if (command.argv.len != 0)
	{
		if (builtin_index(*(char **)vec_get(&command.argv, 0)) != -1)
			return (run_builtin_pipe(&command, 0, pipeinfo->pipe_fds, 0));
	}
	return (run_single_pipe_command(&command, pipeinfo->pipe_fds, 0, 0));
}

int last_pipe_command(t_pipe *pipeinfo, int i)
{
	t_command	command;
	int			ret;
	
	ret = prepare_pipe_command(&command, pipeinfo, i);
	if (ret != 0)
	{
		handle_parent(1, pipeinfo->pipe_fds, 0);
		return (ret);
	}
	if (command.argv.len != 0)
	{
		if (builtin_index(*(char **)vec_get(&command.argv, 0)) != -1)
			return (run_builtin_pipe(&command, 1, pipeinfo->pipe_fds, 0));
	}
	return (run_single_pipe_command(&command, pipeinfo->pipe_fds, 0, 1));
}

int	middle_pipe_command(t_pipe *pipeinfo, int i)
{
	int			pipe2_fds[2];
	t_command	command;
	int			ret;

	if (pipe(pipe2_fds) < 0)
	{
		perror("pipe failed");
		return (-1);
	}
	ret = prepare_pipe_command(&command, pipeinfo, i);
	if (ret != 0)
	{
		handle_parent(2, pipeinfo->pipe_fds, pipe2_fds);
		return (ret);
	}
	if (command.argv.len != 0)
	{
		if (builtin_index(*(char **)vec_get(&command.argv, 0)) != -1)
			return (run_builtin_pipe(&command, 2, pipeinfo->pipe_fds, pipe2_fds));
	}
	return (run_single_pipe_command(&command, pipeinfo->pipe_fds, pipe2_fds, 2));
}

int	pipe_commands(t_pipe *pipeinfo)
{
	int	i;

	if (pipe(pipeinfo->pipe_fds) < 0)
	{
		perror("pipe failed");
		return (-1);
	}
	i = 0;
	while (i < pipeinfo->command_count)
	{
		if (i == 0)
			pipeinfo->process_ids[i] = first_pipe_commmand(pipeinfo, i);
		else if (i == pipeinfo->command_count - 1)
			pipeinfo->process_ids[i] = last_pipe_command(pipeinfo, i);
		else
			pipeinfo->process_ids[i] = middle_pipe_command(pipeinfo, i);
		if (pipeinfo->process_ids[i] == -1)
			return (-1);
		i++;
	}
	return (1);
}
