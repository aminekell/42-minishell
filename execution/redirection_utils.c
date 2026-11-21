/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:07:37 by zaissi            #+#    #+#             */
/*   Updated: 2025/07/12 12:43:53 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_fd_path(char *file)
{
	char	buffer[1024];
	char	*tmp;
	char	*path;

	getcwd(buffer, 1024);
	tmp = ft_strjoin(buffer, "/");
	path = ft_strjoin(tmp, file);
	ft_free(tmp);
	return (path);
}

int	ft_get_file(char *file, int type)
{
	char	*path;
	int		fd;

	if (!file || !file[0])
		return (-1);
	if (file[0] == '.' || file[0] == '/')
		return (get_file_with_path(file, type));
	else
	{
		path = ft_strjoin("./", file);
		fd = get_file_with_path(path, type);
		return (ft_free(path), fd);
	}
	if (type == 1)
	{
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		return (ft_free(path), fd);
	}
	if (type == 3)
	{
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0644);
		return (ft_free(path), fd);
	}
	return (ft_free(path), -1);
}

void	check_fd(int fd, char *str)
{
	if (fd < 0)
	{
		write(2, "MiniShell: ", 12);
		ft_putstr_fd(str, 2);
		write(2, ": can not access this file\n", 28);
		exit(1);
	}
}

int	ft_check(t_redir *ptr)
{
	int	l;

	l = 0;
	while (ptr)
	{
		if (ptr->type == 0 || ptr->type == 2)
			l = 1;
		ptr = ptr->next;
	}
	return (l);
}
