/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 13:45:56 by akella            #+#    #+#             */
/*   Updated: 2025/07/12 18:51:27 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*creat_cmd(t_list *list)
{
	char	*path;
	char	*cmd;

	cmd = NULL;
	path = NULL;
	if (!list->tokens || !list->tokens[0])
		return (exit(0), NULL);
	if (list->tokens[0][0] == 0)
		return (NULL);
	cmd = return_cmd(list->tokens, list->env);
	return (cmd);
}

int	exe(t_help *help)
{
	char		**env;
	char		*cmd;
	struct stat	sb;

	if (!ft_commands(help))
		exit(0);
	cmd = creat_cmd(help->list);
	if (!cmd)
		print_err(2, help->list->tokens[0]);
	env = env_return(help->list->env);
	if (execve(cmd, help->list->tokens, env) < 0)
	{
		if (stat(cmd, &sb) == 0 && S_ISDIR(sb.st_mode))
			print_err(EISDIR, cmd);
		write(2, "MiniShell: ", 12);
		perror(cmd);
		free_token(env);
		if (errno == ENOENT)
			exit(127);
		else
			exit(126);
	}
	return (0);
}

int	befor_exe(t_help *help)
{
	if (help->list->type == TYPE_PIPE)
		pipe(help->main_pipe);
	if (!ft_strcmp(help->list->tokens[0], "exit")
		&& (help->first && help->list->type == 3))
	{
		child_process(help);
		if (!ft_commands(help))
			return (-1);
	}
	if (help->first && help->list->type == 3 && (!help->list->redirections))
		if (!ft_commands(help))
			return (-1);
	return (0);
}

void	first_build(t_help *help, pid_t pids[1024], int *i)
{
	while (help->list)
	{
		if (execute_heredoc(help->list, help))
		{
			closeall();
			break ;
		}
		if (befor_exe(help) == -1)
		{
			help->list = help->list->next;
			continue ;
		}
		creat_process(help);
		pids[(*i)++] = help->pid;
		help->list = help->list->next;
	}
}

void	execute_list(t_help *help)
{
	pid_t	*pids;
	int		i;

	(1) && (help->first = 1, i = 0);
	(1) && (help->prev_pipe[0] = -1, help->prev_pipe[1] = -1);
	pids = ft_malloc(sizeof(pid_t) * ft_list_size(help->list));
	first_build(help, pids, &i);
	exe_files(help);
	wait_command_to_finish(pids, i, help);
	unlink("/tmp/.heredoc");
}
