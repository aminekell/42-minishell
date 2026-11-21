/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 00:08:23 by zaissi            #+#    #+#             */
/*   Updated: 2025/07/05 17:23:39 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**env_return(t_env *env)
{
	char	**str;
	int		len;
	t_env	*tmp;

	tmp = env;
	len = 0;
	while (env)
	{
		len++;
		env = env->next;
	}
	str = ft_malloc(sizeof(char **) * (len + 1));
	len = 0;
	while (tmp)
	{
		str[len++] = ft_strdup(tmp->value);
		tmp = tmp->next;
	}
	str[len] = NULL;
	return (str);
}

char	*ft_getenv(t_env *env, char *str)
{
	t_env	*tmp;
	char	*var;

	tmp = env;
	var = NULL;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, str))
		{
			var = ft_strdup(tmp->data);
			return (var);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
