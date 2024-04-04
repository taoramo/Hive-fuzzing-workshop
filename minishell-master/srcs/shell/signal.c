/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:17:30 by toramo            #+#    #+#             */
/*   Updated: 2024/02/09 15:17:31 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	toggle_carret(int is_on)
{
	struct termios	new_attr;

	tcgetattr(STDIN_FILENO, &new_attr);
	if (!is_on)
		new_attr.c_lflag &= ~ECHOCTL;
	else
		new_attr.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_attr);
}

void	new_prompt(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return ;
}

void	signal_interactive(void)
{
	struct sigaction	sa;
	struct sigaction	sb;

	toggle_carret(0);
	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = new_prompt;
	sigaction(SIGINT, &sa, 0);
	ft_bzero(&sb, sizeof(sa));
	sb.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sb, 0);
}

void	print_new_line(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
}

void	signal_non_interactive(void)
{
	struct sigaction	sa;

	toggle_carret(1);
	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = print_new_line;
	sigaction(SIGINT, &sa, 0);
	sigaction(SIGQUIT, &sa, 0);
}
