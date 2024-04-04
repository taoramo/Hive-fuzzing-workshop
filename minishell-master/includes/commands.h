/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:09:06 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/15 13:34:25 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>

# include "libft.h"
# include "minishell.h"

typedef struct s_command
{
	t_vec	argv;
	t_vec	redirects;
	pid_t	process_id;
	t_vec	*env;
}	t_command;

typedef struct s_redirect
{
	int	origial_fd;
	int	new_fd;
}	t_redirect;

typedef struct s_pipe
{
	char	**command_strs;
	int		command_count;
	int		*process_ids;
	int		pipe_fds[2];
	int		last_return;
	t_vec	env;
	t_vec	*heredoc_fds;
}	t_pipe;

typedef struct s_envinfo
{
	t_vec	*env;
	int		*last_return;
	t_vec	heredoc_fds;
}	t_envinfo;

int		ft_isspace(int c);
int		quote_length(char *str);
int		redirect_length(char *str);

int		prepare_command(t_command *command, char *command_str,
			t_envinfo envinfo, int i);
int		prepare_pipe_command(t_command *command, t_pipe *pipeinfo, int i);
int		split_command(t_vec *strs, char *str);
int		split_expanded_command(t_vec *argv);
int		extract_files(t_command *command, int heredoc_fd);
char	*get_redirect_filename(char	*str);
int		add_path(char **command_ptr, t_vec *env);

int		run_command(char *str, t_envinfo envinfo);
void	apply_redirect(void	*param);
pid_t	execute_command(t_vec argv, t_vec *env);

int		run_builtin(t_command *command);
int		run_builtin_pipe(t_command *command,
			int pos, int pipe_fds[], int pipe2_fds[]);

int		pipex(char *pipe_str, t_envinfo envinfo);
int		count_commands(char **strs);
int		pipe_commands(t_pipe *pipeinfo);
void	apply_pipe_redirect(t_command *command, int in_fd, int out_fd);
void	handle_parent(int pos, int pipe_fds[], int pipe2_fds[]);
void	handle_child(t_command *command,
			int pipe_fds[], int pipe2_fds[], int pos);

#endif
