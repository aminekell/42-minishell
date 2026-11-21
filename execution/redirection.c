/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 00:22:29 by zaissi            #+#    #+#             */
/*   Updated: 2025/07/15 19:21:33 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_file_with_path(char *file, int type)
{
	if (!access(file, R_OK) && type == 0)
		return (open(file, O_RDONLY));
	if (!access(file, W_OK) && type == 1)
		return (open(file, O_CREAT | O_WRONLY, 0644));
	if (!access(file, W_OK) && type == 3)
		return (open(file, O_APPEND | O_CREAT | O_WRONLY, 0644));
	if (type == 1)
		return (open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644));
	if (type == 3)
		return (open(file, O_CREAT | O_WRONLY | O_APPEND, 0644));
	return (-1);
}

void	get_fd(t_redir *redirection, int fd[2], t_help *help)
{
	if (redirection->type == 2 && redirection->filename != NULL)
	{
		fd[0] = help->fd;
		check_fd(fd[0], redirection->filename);
	}
	else
	{
		ambigios_check(redirection->filename);
		if (redirection->type == 0 && redirection->filename != NULL)
		{
			fd[0] = ft_get_file(redirection->filename, redirection->type);
			check_fd(fd[0], redirection->filename);
		}
		if (redirection->type == 1 && redirection->filename != NULL)
			fd[1] = ft_get_file(redirection->filename, redirection->type);
		if (redirection->filename != NULL && redirection->type == 3)
			fd[1] = ft_get_file(redirection->filename, redirection->type);
		if ((redirection->type == 1 || redirection->type == 3)
			&& redirection->filename)
		{
			check_fd(fd[1], redirection->filename);
			dup2(fd[1], STDOUT_FILENO);
		}
	}
}

int	execute_redirection(t_redir *redirection, int fd[2], t_help *help)
{
	while (redirection)
	{
		get_fd(redirection, fd, help);
		if (redirection->type == 2 || redirection->type == 0)
		{
			dup2(fd[0], STDIN_FILENO);
			check_fd(fd[0], redirection->filename);
		}
		if (redirection->type == 0 || redirection->type == 2)
			close(fd[0]);
		else if (redirection->type == 1 || redirection->type == 3)
			close(fd[1]);
		redirection = redirection->next;
	}
	return (0);
}
