/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:31:05 by zaissi            #+#    #+#             */
/*   Updated: 2025/07/12 19:31:08 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_redir(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir;
		redir = redir->next;
		ft_free(tmp->filename);
		ft_free(tmp);
	}
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp->data);
		free(tmp);
	}
}

void	free_list(t_list *list)
{
	t_list	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free_token(tmp->tokens);
		ft_free(tmp->argv);
		free_redir(tmp->redirections);
		free(tmp);
	}
}

void	free_export(t_export *exp)
{
	t_export	*tmp;

	while (exp)
	{
		tmp = exp;
		exp = exp->next;
		free(tmp->value);
		free(tmp);
	}
}

void	free_help(t_help *help)
{
	if (!help)
		return ;
	ft_free(help);
}
