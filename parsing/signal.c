/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 01:09:14 by akella            #+#    #+#             */
/*   Updated: 2025/07/05 20:23:27 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	setup_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	rl_catch_signals = 0;
}

void	restore_parent_signals(t_help *help)
{
	int	term_sig;

	if (WIFSIGNALED(help->status))
	{
		term_sig = WTERMSIG(help->status);
		if (term_sig == SIGINT)
		{
			write(1, "\n", 1);
			exit_status(1, 130);
		}
		else if (term_sig == SIGQUIT)
		{
			write(2, "Quit: 3\n", 9);
			exit_status(1, 131);
		}
	}
	signal(SIGINT, sigint_handler);
}

void	child_signel(t_help *help)
{
	(void)help;
	signal(SIGINT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	her(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(130);
}

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit_status(1, 1);
	if (check_print(0, 0) == 0)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
