/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wird_cart_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:58:09 by zaissi            #+#    #+#             */
/*   Updated: 2025/07/04 23:17:50 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_size(char **token, char **str, int i)
{
	int	len;
	int	size;

	len = 0;
	size = 0;
	while (token[len])
	{
		if (len < i)
			size++;
		else
		{
			i = 0;
			while (str[i])
			{
				if (mutche_filename(str[i], token[len]))
					size++;
				else if (len == i)
					size++;
				i++;
			}
		}
		len++;
	}
	return (size);
}

void	slash_token(struct dirent *enty, char *token, char **new, int *size)
{
	if (token[0] == '.')
	{
		if (enty->d_type == DT_DIR)
			new[*size] = ft_strjoin(enty->d_name, "/");
		else
			new[*size] = ft_strdup(enty->d_name);
		(*size)++;
	}
	else if ((int)enty->d_type == DT_DIR && enty->d_name[0] != '.')
	{
		new[*size] = ft_strjoin(enty->d_name, "/");
		(*size)++;
	}
	else if (enty->d_name[0] != '.')
	{
		new[*size] = ft_strdup(enty->d_name);
		(*size)++;
	}
}

void	regular_token(struct dirent *enty, char *token, char **new, int *size)
{
	if (!mutche_filename(token, enty->d_name))
		return ;
	if (token[0] == '.')
	{
		new[*size] = ft_strdup(enty->d_name);
		(*size)++;
	}
	else if (enty->d_name[0] != '.')
	{
		new[*size] = ft_strdup(enty->d_name);
		(*size)++;
	}
}

int	get_size_len(char *str)
{
	int	i;
	int	flag;
	int	size;
	int	len;

	(1) && (i = 0, flag = 0, size = 0, len = 0);
	while (str[i])
	{
		if (str[i] == '*' && flag == 0)
		{
			size++;
			flag = 1;
		}
		else if (str[i] != '*')
		{
			len++;
			flag = 0;
		}
		else if (str[i] != '*' && len != 0)
			len++;
		i++;
	}
	return (len + size);
}

int	expand_token_array(t_list *node, int i, char **str)
{
	char	**tmp_token;
	char	*tmp;

	tmp = NULL;
	tmp_token = wirdcart(node->tokens, i);
	if (!tmp_token)
		return (1);
	free_token(node->tokens);
	node->tokens = tmp_token;
	if (*str)
	{
		tmp = skip_all_wird(*str);
		if (node->tokens[i] && !ft_strcmp(node->tokens[i], tmp))
		{
			free(node->tokens[i]);
			node->tokens[i] = ft_strdup(*str);
		}
		ft_free(tmp);
		tmp = NULL;
	}
	return (0);
}
