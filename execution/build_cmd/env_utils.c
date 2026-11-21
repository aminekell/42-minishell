/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:39:37 by zaissi            #+#    #+#             */
/*   Updated: 2025/07/01 03:12:04 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	edit_env_values(char *str, t_env *env)
{
	char	*tmp;

	if (get_equal(str))
		add_to_data(env, str);
	else
	{
		ft_free(env->data);
		ft_free(env->value);
		env->data = data(str);
		tmp = ft_strjoin(env->key, "=");
		env->value = ft_strjoin(tmp, env->data);
		free(tmp);
	}
}

char	*update_str(char *str)
{
	int		i;
	int		len;
	char	*ptr;

	i = 0;
	len = 0;
	while (str[i])
		i++;
	ptr = ft_malloc(sizeof(char *) * i);
	i = 0;
	while (str[i])
	{
		if (str[i] != '+')
		{
			ptr[len] = str[i];
			len++;
		}
		i++;
	}
	ptr[len] = '\0';
	return (ptr);
}

void	add_to_data(t_env *env, char *str)
{
	int		i;
	char	*old_data;
	char	*new_data;
	int		len;

	(1) && (old_data = ft_strdup(env->data), new_data = data(str));
	ft_free(env->value);
	ft_free(env->key);
	len = (sizeof(char *) * (ft_strlen(env->data) + ft_strlen(new_data) + 1));
	ft_free(env->data);
	env->data = ft_malloc(len);
	i = ft_strlcpy_without_term(env->data, old_data);
	ft_free(old_data);
	len = 0;
	while (new_data[len])
	{
		env->data[i] = new_data[len];
		len++;
		i++;
	}
	env->data[i] = '\0';
	allocat_data(str, env, new_data);
}

int	get_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	ft_strlcpy_without_term(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	return (i);
}
