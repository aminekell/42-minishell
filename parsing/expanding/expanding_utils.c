/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:50:44 by akella            #+#    #+#             */
/*   Updated: 2025/07/12 22:49:16 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expande.h"

char	*get_env_value(const char *name, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, name) == 0)
			return (env->data);
		env = env->next;
	}
	return (NULL);
}

int	handle_single_quote(const char *str, int *idx, int len)
{
	int	pos;

	pos = *idx + 1;
	len++;
	while (str[pos] && str[pos] != '\'')
	{
		if (str[pos] == '*')
			len += 2;
		else
			len += 1;
		pos++;
	}
	if (str[pos] == '\'')
		pos++;
	len++;
	*idx = pos;
	return (len);
}

int	handle_literal_double(const char *str, int *idx, int len)
{
	int	pos;

	pos = *idx + 1;
	while (str[pos] && str[pos] != '"')
	{
		len++;
		pos++;
	}
	if (str[pos] == '"')
		pos++;
	*idx = pos;
	return (len);
}

int	handle_literal_single(const char *str, int *idx, int len)
{
	int	pos;

	pos = *idx + 1;
	while (str[pos] && str[pos] != '\'')
	{
		len++;
		pos++;
	}
	if (str[pos] == '\'')
		pos++;
	*idx = pos;
	return (len);
}

void	copy_squoted(int *dst_idx, char **src, char **dst)
{
	int	i;

	i = *dst_idx;
	empty(1, 1);
	ambigios(1, 0);
	(*src)++;
	while (**src && **src != '\'')
	{
		(*dst)[i++] = *(*src)++;
		if ((*dst)[i - 1] == '*')
			(*dst)[i++] = '\a';
	}
	if (**src == '\'')
		(*src)++;
	*dst_idx = i;
}
