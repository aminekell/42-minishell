/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 09:38:39 by zaissi            #+#    #+#             */
/*   Updated: 2025/07/12 19:08:39 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_path(char *str, char *cmd)
{
	char		**env;
	char		*path;
	char		*old;
	int			i;
	struct stat	st;

	if (!str || !cmd)
		ft_exit(1);
	(1) && (env = ft_split(str, ':'), i = 0);
	while (env[i])
	{
		old = ft_strjoin(env[i], "/");
		path = ft_strjoin(old, cmd);
		ft_free(old);
		if (!access(path, X_OK))
			if (stat(path, &st) == 0 && S_ISREG(st.st_mode))
				return (free_token(env), path);
		ft_free(path);
		i++;
	}
	return (free_token(env), NULL);
}

void	execute_command(t_list *list, t_export **ptr)
{
	t_help			*help;

	if (!list->tokens)
		return ;
	if (ft_list_size(list) >= 1392)
	{
		write(2, "Minishell: fork: Resource temporarily unavailable\n", 51);
		exit_status(1, 1);
		return ;
	}
	help = help_init(list, ptr);
	if (!help)
		return ;
	tcgetattr(STDIN_FILENO, &help->original_term);
	execute_list(help);
	tcsetattr(STDIN_FILENO, TCSANOW, &help->original_term);
	wait(NULL);
	free_help(help);
	return ;
}

int	check_is_dir(char *str, int *status)
{
	char	*ptr;
	int		i;
	int		j;
	DIR		*dir;

	(1) && (i = ft_strlen(str) - 1, j = 0);
	while (str[i] && str[i] != '/')
		i--;
	ptr = ft_malloc(sizeof(char *) * ft_strlen(str) - (ft_strlen(str) - i));
	while (str[j] && j < i)
	{
		ptr[j] = str[j];
		j++;
	}
	ptr[j] = '\0';
	dir = opendir(ptr);
	if (!dir)
	{
		if (open(ptr, O_RDONLY) != -1)
			return ((*status)++, (*status)++, (*status)++, ft_free(ptr), 1);
	}
	else
		closedir(dir);
	return (ft_free(ptr), 0);
}

char	*return_cmd(char **token, t_env *env)
{
	char	*path;
	char	*cmd;

	(1) && (cmd = NULL, path = NULL);
	if (ft_strchr_int(token[0], '/'))
	{
		path = ft_getenv(env, "PATH");
		if (path)
		{
			cmd = ft_path(path, token[0]);
			return (ft_free(path), cmd);
		}
		else
		{
			cmd = ft_strjoin("./", token[0]);
			if (!access(cmd, X_OK))
				return (cmd);
			else if (open(cmd, O_RDONLY) != -1)
				return (ft_free(cmd), token[0]);
		}
		return (NULL);
	}
	else
		return (token[0]);
}
