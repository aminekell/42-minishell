/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 19:53:08 by zaissi            #+#    #+#             */
/*   Updated: 2025/07/08 14:26:16 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exe_pwd(t_env *env)
{
	char	buffer[1024];
	char	*new;

	if (!getcwd(buffer, 1024))
	{
		getcwd(buffer, 1024);
		new = ft_getenv(env, "PWD");
		write(1, new, ft_strlen(new));
		ft_free(new);
	}
	else
	{
		new = buffer;
		write(1, new, ft_strlen(new));
	}
	write(1, "\n", 1);
	return (0);
}

void	exe_files(t_help *help)
{
	if (!help || !help->list)
		return ;
	if (!help->list->tokens || !help->list->tokens[0])
	{
		if (help->list->redirections)
			ft_get_file(help->list->redirections->filename,
				help->list->redirections->type);
	}
}

int	execute_heredoc(t_list *list, t_help *help)
{
	t_redir	*red;
	int		res;

	res = 0;
	if (list->redirections)
	{
		red = list->redirections;
		while (red)
		{
			if (red->type == 2 && red->filename)
			{
				if (heredoc(red->filename, list->env, help) == 130)
				{
					exit_status(1, 1);
					return (1);
				}
			}
			red = red->next;
		}
	}
	return (max_heredoc(1, 0), 0);
}
