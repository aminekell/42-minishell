/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wird_cart_help.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:06:15 by zaissi            #+#    #+#             */
/*   Updated: 2025/07/04 21:33:43 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	later_token(char *token, char **str, char **filter, int *size)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (token[0] == '.')
		{
			if (mutche_filename(str[i], token))
			{
				filter[*size] = ft_strdup(token);
				(*size)++;
				break ;
			}
		}
		else
		{
			if (mutche_filename(str[i], token))
			{
				filter[*size] = ft_strdup(token);
				(*size)++;
				break ;
			}
		}
		i++;
	}
}

int	count_total_entries(char **token)
{
	int				total;
	int				i;

	i = 0;
	total = 0;
	while (token[i])
	{
		if (ft_strchr(token[i], '*') == NULL)
			total++;
		else
			total = total_wird(total, token[i]);
		i++;
	}
	return (total);
}

char	*push_to_ptr(char *str, char *ptr, int len)
{
	int	i;
	int	flag;

	(1) && (i = 0, flag = 0);
	while (str[i])
	{
		if (str[i] == '*' && flag == 0)
		{
			ptr[len] = '*';
			(1) && (len++, flag = 1);
		}
		else if (str[i] != '*')
		{
			ptr[len] = str[i];
			(1) && (len++, flag = 0);
		}
		else if (str[i] != '*' && len != 0)
		{
			ptr[len] = str[i];
			len++;
		}
		i++;
	}
	ptr[len] = '\0';
	return (ptr);
}

t_list	*get_wirdcart(t_list **list)
{
	t_list	*ptr;

	ptr = *list;
	while (ptr)
	{
		command_tokens(ptr);
		ptr = ptr->next;
	}
	return (*list);
}
