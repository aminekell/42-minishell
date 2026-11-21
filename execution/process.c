/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:28:32 by zaissi            #+#    #+#             */
/*   Updated: 2025/07/09 16:51:38 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clean_heredoc(t_redir *redirection)
{
	while (redirection)
	{
		if (redirection)
		{
			if (redirection->type == 2
				&& redirection->filename != NULL)
				unlink("/tmp/.heredoc");
			redirection = redirection->next;
		}
	}
}

void	child_process(t_help *help)
{
	if (help->list->type == TYPE_PIPE && !isatty(help->main_pipe[1]))
		dup2(help->main_pipe[1], STDOUT_FILENO);
	if (help->list->redirections)
	{
		if (execute_redirection(help->list->redirections, help->main_pipe,
				help))
		{
			closeall();
			exit(1);
		}
	}
	if (help->list->type == TYPE_PIPE)
		dup2(help->main_pipe[1], STDOUT_FILENO);
	if (!help->first && !ft_check(help->list->redirections))
		dup2(help->prev_pipe[0], STDIN_FILENO);
	if (help->main_pipe[0] != -1)
		close(help->main_pipe[0]);
	if (help->main_pipe[1] != -1)
		close(help->main_pipe[1]);
	if (help->prev_pipe[0] != -1)
		close(help->prev_pipe[0]);
	if (help->prev_pipe[1] != -1)
		close(help->prev_pipe[1]);
}

int	parint_process(t_help *help)
{
	if (!help->first)
	{
		close(help->prev_pipe[0]);
		close(help->prev_pipe[1]);
	}
	close(help->main_pipe[1]);
	if (help->list->type != 3 && help->list->type != 5)
	{
		help->prev_pipe[0] = help->main_pipe[0];
		help->prev_pipe[1] = -1;
	}
	else
	{
		close(help->main_pipe[0]);
		help->prev_pipe[0] = -1;
		help->prev_pipe[1] = -1;
	}
	return (0);
}

int	creat_process(t_help *help)
{
	check_print(1, 1);
	signal(SIGINT, sigint_handler);
	help->pid = fork();
	if (help->pid == -1)
	{
		perror("Minishell");
		exit(1);
	}
	if (help->pid == 0)
	{
		child_signel(help);
		child_process(help);
		if (exe(help))
			exit(127);
	}
	else
	{
		help->first = parint_process(help);
		if (bonus_part(help->list, &help->status, help->bonus_type))
			return (1);
	}
	return (0);
}

void	wait_command_to_finish(int pids[1024], int max, t_help *help)
{
	int	i;

	i = 0;
	signal(SIGINT, SIG_IGN);
	while (i < max)
	{
		waitpid(pids[i], &help->status, 0);
		i++;
	}
	restore_parent_signals(help);
	check_print(1, 0);
	exit_quite(1, 0);
	if (WIFEXITED(help->status) && WEXITSTATUS(help->status) == 127)
		exit_status(1, 127);
	if (WIFEXITED(help->status) && WEXITSTATUS(help->status) == 126)
		exit_status(1, 126);
	if (WIFEXITED(help->status) && WEXITSTATUS(help->status))
		exit_status(1, WEXITSTATUS(help->status));
	closeall();
}
