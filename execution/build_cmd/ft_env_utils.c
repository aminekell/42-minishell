/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:39:16 by zaissi            #+#    #+#             */
/*   Updated: 2025/07/08 16:01:44 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_equl(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && i > 0)
			return (1);
		i++;
	}
	return (0);
}

int	is_key(char *str, t_env *env)
{
	int		i;
	char	*key;

	i = 0;
	key = ft_malloc(sizeof(char) * (key_len(str) + 1));
	while (str[i] && str[i] != '=')
	{
		key[i] = str[i];
		i++;
	}
	key[i] = '\0';
	i = 0;
	while (env)
	{
		if (!ft_strcmp(env->key, key))
		{
			return (ft_free(key), i);
		}
		env = env->next;
		i++;
	}
	ft_free(key);
	return (0);
}

int	in_export(char *str, t_export *ptr)
{
	while (ptr)
	{
		if (!ft_strcmp(str, ptr->value))
			return (1);
		ptr = ptr->next;
	}
	return (0);
}
