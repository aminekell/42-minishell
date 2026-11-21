/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splite_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:07:57 by akella            #+#    #+#             */
/*   Updated: 2025/07/10 22:39:40 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expande.h"

void	copy_literal_double(int *dst_idx, char **src, char **dst)
{
	int	i;

	i = *dst_idx;
	(*src)++;
	while (**src && **src != '"')
		(*dst)[i++] = *(*src)++;
	if (**src == '"')
		(*src)++;
	*dst_idx = i;
}

static void	handle_dq_dollar(char **src, char **dst, int *i, t_env *env)
{
	char	*ret_str;
	char	next;

	if ((*src)[1] == '?')
	{
		ret_str = ft_itoa(exit_status(0, 0));
		if (ret_str)
		{
			insert_exit_status(dst, ret_str, i, src);
			free(ret_str);
		}
	}
	else
	{
		next = (*src)[1];
		if (!((next >= 'A' && next <= 'Z')
				|| (next >= 'a' && next <= 'z')
				|| (next >= '0' && next <= '9')
				|| next == '_'))
			(*dst)[(*i)++] = *(*src)++;
		else
			copy_var(i, src, dst, env);
	}
}

void	copy_dquoted(int *dst_idx, char **src, char **dst, t_env *env)
{
	int	i;

	i = *dst_idx;
	empty(1, 1);
	(*src)++;
	while (**src && **src != '"')
	{
		if (**src == '$')
		{
			handle_dq_dollar(src, dst, &i, env);
			if (i > 0 && ((*dst)[i - 1] == '*'))
				(*dst)[i++] = '\a';
		}
		else
		{
			(*dst)[i++] = *(*src)++;
			if ((*dst)[i - 1] == '*')
				(*dst)[i++] = '\a';
		}
	}
	if (**src == '"')
		(*src)++;
	*dst_idx = i;
}

void	copy_exit_status(int *dst_idx, char **src, char **dst)
{
	int		i;
	int		k;
	char	*ret_str;

	i = *dst_idx;
	ret_str = ft_itoa(exit_status(0, 0));
	if (ret_str)
	{
		k = 0;
		while (ret_str[k])
			(*dst)[i++] = ret_str[k++];
		free(ret_str);
	}
	*src += 2;
	*dst_idx = i;
}

void	copy_var(int *dst_idx, char **src, char **dst, t_env *env)
{
	int		start;
	int		i;
	int		k;
	char	*key;
	char	*val;

	if ((*src)[1] == '?')
		copy_exit_status(dst_idx, src, dst);
	start = 1;
	i = *dst_idx;
	while (((*src)[start] && (ft_isalnum((*src)[start])
		|| (*src)[start] == '_')))
		start++;
	key = ft_substr(*src + 1, 0, start - 1);
	val = get_env_value(key, env);
	ft_free(key);
	k = 0;
	while (val && val[k])
		(*dst)[i++] = val[k++];
	*src += start;
	*dst_idx = i;
}
