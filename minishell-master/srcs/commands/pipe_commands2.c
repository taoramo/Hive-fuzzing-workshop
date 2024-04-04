/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_commands2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:36:19 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/13 18:36:19 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

void	apply_pipe_redirect(t_command *command, int in_fd, int out_fd)
{
	if (in_fd != 0)
	{
		if (dup2(in_fd, 0) == -1)
			perror("dup failed");
	}
	if (out_fd != 1)
	{
		if (dup2(out_fd, 1) == -1)
			perror("dup failed");
	}
	vec_iter(&command->redirects, apply_redirect);
}

void	handle_parent(int pos, int pipe_fds[], int pipe2_fds[])
{
	if (pos == 0)
		close(pipe_fds[1]);
	else if (pos == 1)
		close(pipe_fds[0]);
	else
	{
		close(pipe_fds[0]);
		close(pipe2_fds[1]);
		pipe_fds[0] = pipe2_fds[0];
	}
}

void	handle_child(t_command *command, int pipe_fds[], int pipe2_fds[], int pos)
{
	if (pos == 0)
	{
		close(pipe_fds[0]);
		apply_pipe_redirect(command, 0, pipe_fds[1]);
	}
	else if (pos == 1)
	{
		apply_pipe_redirect(command, pipe_fds[0], 1);
	}
	else
	{
		close(pipe2_fds[0]);
		apply_pipe_redirect(command, pipe_fds[0], pipe2_fds[1]);
	}
	if (command->argv.len == 0)
		exit(1);
	execute_command(command->argv, command->env);
}
