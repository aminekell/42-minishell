/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:32:16 by zaissi            #+#    #+#             */
/*   Updated: 2025/07/04 23:29:38 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	total_wird(int total, char *str)
{
	int				count;
	DIR				*dir;
	struct dirent	*entry;

	count = 0;
	dir = opendir(".");
	if (!dir)
		return (-1);
	entry = readdir(dir);
	while (entry)
	{
		if (mutche_filename(str, entry->d_name))
			count++;
		entry = readdir(dir);
	}
	closedir(dir);
	if (count == 0)
		total++;
	else
		total += count;
	return (total);
}

int	wildcard_token(char *token, char **new, int *size, int *old)
{
	DIR				*dir;
	struct dirent	*enty;
	int				token_len;

	dir = opendir(".");
	if (!dir)
		return (1);
	*old = *size;
	enty = readdir(dir);
	while (enty)
	{
		token_len = ft_strlen(token);
		if (token_len > 0 && token[token_len - 1] == '/')
			slash_token(enty, token, new, size);
		else
			regular_token(enty, token, new, size);
		enty = readdir(dir);
	}
	if (*old == *size)
	{
		new[*size] = ft_strdup(token);
		(*size)++;
	}
	closedir(dir);
	return (0);
}

void	command_tokens(t_list *node)
{
	int		i;
	int		pos;
	char	*str;
	char	*back;
	int		j;

	(1) && (i = 0, pos = -1, str = NULL);
	while (node->tokens[i])
	{
		back = ft_strdup(node->tokens[i]);
		j = token_wildcard(&node->tokens[i], &pos, &str);
		if (j != -1 && pos == j)
		{
			if (expand_token_array(node, i, &str))
			{
				ft_free(node->tokens[i]);
				node->tokens[i] = ft_strdup(back);
				ft_free(back);
				break ;
			}
		}
		ft_free(back);
		i++;
	}
	ft_free(str);
}
