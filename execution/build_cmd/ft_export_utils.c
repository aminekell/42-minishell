/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:37:21 by zaissi            #+#    #+#             */
/*   Updated: 2025/05/21 10:15:33 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	delete_export(t_export **ptr, char *str)
{
	t_export	*temp;
	t_export	*prev;

	temp = *ptr;
	prev = NULL;
	while (temp != NULL)
	{
		if (!ft_strcmp(temp->value, str))
		{
			if (prev == NULL)
			{
				*ptr = temp->next;
			}
			else
			{
				prev->next = temp->next;
			}
			free(temp->value);
			free(temp);
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
}

t_export	*get_new_value(char *str)
{
	int			i;
	t_export	*ptr;

	i = 0;
	ptr = ft_malloc(sizeof(t_export));
	ptr->value = ft_malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		ptr->value[i] = str[i];
		i++;
	}
	ptr->value[i] = '\0';
	ptr->next = NULL;
	return (ptr);
}

char	*data(char *str)
{
	int		i;
	int		j;
	int		old;
	char	*data;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	j = 0;
	i++;
	old = i;
	while (str[i])
		(1) && (j++, i++);
	data = ft_malloc(sizeof(char) * (j + 1));
	i = 0;
	while (str[old])
	{
		data[i] = str[old];
		i++;
		old++;
	}
	data[i] = '\0';
	return (data);
}

char	*get_key(char *str)
{
	int		i;
	char	*key;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	key = ft_malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] && str[i] != '=')
	{
		key[i] = str[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}
