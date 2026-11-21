/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 01:29:01 by zaissi            #+#    #+#             */
/*   Updated: 2025/07/10 20:20:54 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	unset_env(char *str, t_env **env)
{
	t_env	*curr;
	t_env	*prev;
	t_env	*next;

	(1) && (prev = NULL, curr = *env);
	while (curr)
	{
		if (!ft_strcmp(str, curr->key) && ft_strcmp(str, "_"))
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			next = curr->next;
			ft_free(curr->key);
			ft_free(curr->value);
			ft_free(curr->data);
			ft_free(curr);
			curr = next;
			continue ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	unset_export(char *str, t_export **env)
{
	t_export	*curr;
	t_export	*prev;
	t_export	*tmp;

	(1) && (prev = NULL, curr = *env);
	while (curr)
	{
		if (!ft_strcmp(str, curr->value))
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			tmp = curr;
			curr = curr->next;
			free(tmp->value);
			free(tmp);
			continue ;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	exe_unset(char **args, t_env **env, t_export **ptr)
{
	int	i;

	i = 1;
	if (!args || !args[1])
		return (0);
	while (args[i])
	{
		if (args[i][0] == '-' || args[i][0] == '=')
			return (1);
		unset_env(args[i], env);
		unset_export(args[i], ptr);
		i++;
	}
	return (0);
}

int	exe_cd(char **v, t_env **env_list, t_export **exp)
{
	char	*dir;
	t_env	*ptr;

	ptr = *env_list;
	if (!v || !*v || !v[0])
		return (1);
	dir = get_dir_value(v, *env_list, exp);
	if (!dir)
		return (1);
	ptr = update_env("OLDPWD", ptr);
	if (access(dir, X_OK | R_OK) && !ft_strncmp(dir, "..", 2))
	{
		ft_free(dir);
		dir = ft_getenv(*env_list, "OLDPWD");
	}
	if (chdir(dir) != 0)
		return (ft_free(dir), 1);
	ptr = update_env("PWD", ptr);
	ft_free(dir);
	return (0);
}

int	ft_list_size(t_list *list)
{
	t_list	*ptr;
	int		i;

	ptr = list;
	i = 0;
	while (ptr)
	{
		i++;
		ptr = ptr->next;
	}
	return (i);
}
