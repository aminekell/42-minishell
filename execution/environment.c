/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 19:52:51 by zaissi            #+#    #+#             */
/*   Updated: 2025/07/03 16:39:54 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**creat_envir(char **str)
{
	int		i;
	int		len;
	char	**ptr;

	(1) && (i = 0, len = 0);
	while (str[i])
	{
		if (ft_strncmp(str[i], "OLDPWD=", 8))
			len++;
		i++;
	}
	ptr = ft_malloc(sizeof(char **) * (len + 1));
	i--;
	len = 0;
	while (str[i])
	{
		if (ft_strncmp(str[i], "OLDPWD=", 8))
		{
			ptr[len] = ft_strdup(str[i]);
			len++;
		}
		i -= 1;
	}
	ptr[len] = NULL;
	return (ptr);
}

t_env	*creat_env(char **tmp1)
{
	t_env	*tmp;
	t_env	*head;
	char	**env;
	int		i;

	i = 0;
	tmp = NULL;
	head = NULL;
	i = 0;
	env = creat_envir(tmp1);
	while (env[i])
	{
		if (!tmp)
			tmp = get_env_list(env[i]);
		else
			tmp->next = get_env_list(env[i]);
		if (!head)
			head = tmp;
		else
			tmp = tmp->next;
		i++;
	}
	return (head);
}
