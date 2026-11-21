/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:35:13 by zaissi            #+#    #+#             */
/*   Updated: 2025/07/04 13:36:55 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*skip_plus(char *str)
{
	char	*ptr;
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (str[i] != '+')
			size++;
		i++;
	}
	ptr = ft_malloc(sizeof(char) * (size + 1));
	(1) && (i = 0, size = 0);
	while (str[i])
	{
		if (str[i] != '+')
		{
			ptr[size] = str[i];
			size++;
		}
		i++;
	}
	ptr[size] = '\0';
	return (ptr);
}

void	add_new_env(char *str, t_env **env)
{
	t_env	*new;
	t_env	*ptr;
	char	*new_str;

	new = *env;
	ptr = *env;
	if (get_equal(str))
	{
		new_str = skip_plus(str);
		ft_free(str);
		str = ft_strdup(new_str);
	}
	new = ft_malloc(sizeof(t_env));
	new->value = ft_strdup(str);
	new->key = get_key(str);
	new->data = data(str);
	new->next = NULL;
	while (ptr)
	{
		if (!ptr->next)
			break ;
		ptr = ptr->next;
	}
	if (ptr)
		ptr->next = new;
}

char	*key_without_plus(char *str)
{
	int		i;
	char	*ptr;

	i = 0;
	while (str[i] && str[i] != '+')
		i++;
	ptr = ft_malloc(sizeof(char *) * i + 1);
	i = 0;
	while (str[i] && str[i] != '+')
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

void	allocat_data(char *str, t_env *env, char *new_data)
{
	ft_free(new_data);
	env->key = key_without_plus(str);
	new_data = ft_strjoin(env->key, "=");
	env->value = ft_strjoin(new_data, env->data);
	ft_free(new_data);
}

int	edit_env(char *str, t_env **env, t_export **head)
{
	int		i;
	int		j;
	char	*ptr;
	char	*key;

	ptr = update_str(str);
	i = is_key(ptr, (*env));
	key = get_key(ptr);
	ft_free(ptr);
	delete_export(head, key);
	ft_free(key);
	if (i != 0)
	{
		j = 0;
		while ((*env))
		{
			if (j == i)
				edit_env_values(str, *env);
			(*env) = (*env)->next;
			j++;
		}
		return (0);
	}
	return (1);
}
