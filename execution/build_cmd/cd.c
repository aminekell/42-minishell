/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:16:06 by zaissi            #+#    #+#             */
/*   Updated: 2025/07/10 20:15:46 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_old_pwd(t_env *head)
{
	char	buffer[1024];
	t_env	*new;
	char	*tmp;

	if (!getcwd(buffer, sizeof(buffer)))
		return ;
	while (head->next)
		head = head->next;
	new = ft_malloc(sizeof(t_env));
	new->key = ft_strdup("OLDPWD");
	new->data = ft_strdup(buffer);
	tmp = ft_strjoin("OLDPWD=", new->data);
	new->value = tmp;
	new->ret = 0;
	new->next = NULL;
	head->next = new;
}

int	update_env_value(t_env *ptr, char *buffer)
{
	char	*key;

	ft_free(ptr->data);
	ft_free(ptr->value);
	ptr->data = ft_strdup(buffer);
	key = ft_strjoin(ptr->key, "=");
	ptr->value = ft_strjoin(key, ptr->data);
	ft_free(key);
	return (1);
}

t_env	*update_env(char *key, t_env *ptr)
{
	char	buffer[1024];
	t_env	*head;
	int		status;

	head = ptr;
	status = 0;
	while (ptr)
	{
		if (!ft_strcmp(key, ptr->key))
		{
			if (!getcwd(buffer, 1024))
			{
				getcwd(buffer, 1024);
				status = update_env_value(ptr, buffer);
			}
			else
				status = update_env_value(ptr, buffer);
		}
		ptr = ptr->next;
	}
	if (status == 0 && ft_strcmp(key, "PWD"))
		add_old_pwd(head);
	return (head);
}

char	*get_old_dir(char *str, t_env *ptr)
{
	while (ptr)
	{
		if (!ft_strcmp(ptr->key, "OLDPWD"))
		{
			free(str);
			str = NULL;
			str = ft_strdup(ptr->data);
		}
		ptr = ptr->next;
	}
	return (str);
}

char	*get_dir_value(char	**token, t_env *env, t_export **ptr)
{
	char	*dir;

	if (ft_tokenlen(token) <= 1)
		dir = ft_getenv(env, "HOME");
	else
		dir = ft_strdup(token[1]);
	unset_export("OLDPWD", ptr);
	return (dir);
}
