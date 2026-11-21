/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _sys_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 00:51:39 by zaissi            #+#    #+#             */
/*   Updated: 2025/05/20 14:32:07 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	key_len(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

int	data_len(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	i++;
	j = 0;
	while (str[i])
	{
		j++;
		i++;
	}
	return (j);
}

t_env	*data_init(char *str)
{
	t_env	*data;
	int		i;
	int		flag;

	data = ft_malloc(sizeof(t_env));
	data->value = ft_malloc(sizeof(char) * ft_strlen(str) + 1);
	data->key = ft_malloc(sizeof(char) * (key_len(str) + 1));
	data->data = ft_malloc(sizeof(char) * (data_len(str) + 1));
	i = 0;
	flag = 0;
	while (str[i])
	{
		data->value[i] = str[i];
		if (str[i] != '=' && flag == 0)
			data->key[i] = str[i];
		else if (flag == 0)
		{
			data->key[i] = '\0';
			flag = 1;
		}
		i++;
	}
	data->value[i] = '\0';
	return (data);
}

t_env	*get_env_list(char *env)
{
	int		i;
	int		j;
	t_env	*data;

	data = data_init(env);
	i = 0;
	j = 0;
	while (env[i] && env[i] != '=')
		i++;
	i++;
	while (env[i])
	{
		data->data[j] = env[i];
		j++;
		i++;
	}
	data->data[j] = '\0';
	data->next = NULL;
	return (data);
}
