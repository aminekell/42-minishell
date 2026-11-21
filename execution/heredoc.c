/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:46:42 by zaissi            #+#    #+#             */
/*   Updated: 2025/07/12 12:27:27 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	store_infile(char *line, t_env *env, int fd)
{
	char	*new;
	int		should_expand;

	new = ft_strjoin(line, "\n");
	ft_free(line);
	should_expand = expand(0, 0);
	if (should_expand == 1)
	{
		new = build_expanded_heredoc(new, env);
		write(fd, new, ft_strlen(new));
	}
	else
		write(fd, new, ft_strlen(new));
	ft_free(new);
}

static void	chaild_heredoc(char *str, t_env *env, int fd, int oldfd)
{
	char	*line;

	close(oldfd);
	signal(SIGINT, her);
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			break ;
		if (!ft_strcmp(str, line))
		{
			ft_free(line);
			break ;
		}
		store_infile(line, env, fd);
	}
	close(fd);
	exit(0);
}

int	heredoc(char *str, t_env *env, t_help *help)
{
	int		status;
	int		pid;
	int		fd;

	if (help->fd != -1)
		close(help->fd);
	fd = open("/tmp/.heredoc", O_CREAT | O_TRUNC | O_WRONLY, 0600);
	help->fd = open("/tmp/.heredoc", O_RDONLY, 0600);
	unlink("/tmp/.heredoc");
	pid = fork();
	if (pid < 0)
		return (closeall(), 1);
	if (pid == 0)
		chaild_heredoc(str, env, fd, help->fd);
	else
	{
		close(fd);
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		signal(SIGINT, sigint_handler);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
			return (closeall(), 130);
	}
	return (expand(1, 0), 0);
}
