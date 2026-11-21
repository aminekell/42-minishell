/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wird_cart.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:53:08 by zaissi            #+#    #+#             */
/*   Updated: 2025/07/04 22:30:10 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_wirdcart_value(char **token)
{
	char	**new;
	int		size;
	int		len;
	int		old;

	new = ft_malloc(sizeof(char *) * (count_total_entries(token) + 1024));
	size = 0;
	len = 0;
	while (token[len])
	{
		old = size;
		if (ft_strchr(token[len], '*') == NULL)
		{
			new[size] = ft_strdup(token[len]);
			size++;
		}
		else
			if (wildcard_token(token[len], new, &size, &old))
				return (NULL);
		len++;
	}
	new[size] = NULL;
	return (new);
}

char	**wirdcart(char **str, int i)
{
	char	**token;
	char	**filter;
	int		len;
	int		size;

	token = get_wirdcart_value(str);
	if (!token)
		return (NULL);
	filter = ft_malloc(sizeof(char *) * (get_size(token, str, i) + 1));
	len = 0;
	size = 0;
	while (token[len])
	{
		if (len < i)
		{
			filter[size] = ft_strdup(token[len]);
			size++;
		}
		else
			later_token(token[len], str, filter, &size);
		len++;
	}
	filter[size] = NULL;
	free_token(token);
	return (filter);
}

int	token_wildcard(char **token, int *pos, char **str)
{
	int	j;

	j = 0;
	while ((*token)[j])
	{
		if ((*token)[j] == '*')
		{
			*pos = j;
			if (*str)
				ft_free(*str);
			*str = ft_strdup(*token);
			ft_free(*token);
			*token = skip_all_wird(*str);
			return (j);
		}
		j++;
	}
	return (-1);
}

char	*skip_all_wird(char *str)
{
	char	*ptr;
	int		len;

	if (!str)
		return (NULL);
	ptr = ft_malloc(sizeof(char) * (get_size_len(str) + 1));
	len = 0;
	ptr = push_to_ptr(str, ptr, len);
	return (ptr);
}

int	get_wirdcart_red(t_redir **red)
{
	t_redir	*ptr;
	int		i;
	int		flag;

	ptr = *red;
	flag = 0;
	while (ptr)
	{
		i = 0;
		while (ptr->filename[i])
		{
			if (ptr->filename[i] == '*')
				return (1);
			i++;
		}
		ptr = ptr->next;
	}
	return (0);
}
