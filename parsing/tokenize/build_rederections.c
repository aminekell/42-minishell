/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_rederections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:46:00 by akella            #+#    #+#             */
/*   Updated: 2025/07/12 23:13:00 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quotes.h"

int	process_red(char **src, char **dst, int *j, t_env *env)
{
	char	next;

	if (**src == '$' && (*src)[1] == '?')
		handle_exit_statu(src, dst, j);
	else if (**src == '$')
	{
		next = (*src)[1];
		if (next != '?' && !is_valid_var_char(next))
			(*dst)[(*j)++] = *(*src)++;
		else
			copy_var_red(j, src, dst, env);
	}
	else
		(*dst)[(*j)++] = *(*src)++;
	return (0);
}

static void	copy_ambiguous(int *i, char **src, char **dst, int end)
{
	int	k;

	ambigios(1, 1);
	k = 0;
	while (k < end)
		(*dst)[(*i)++] = (*src)[k++];
}

static void	copy_valid_value(int *i, char *val, char **dst)
{
	int	k;

	k = 0;
	while (val[k])
		(*dst)[(*i)++] = val[k++];
}

void	copy_var_red(int *dst_idx, char **src, char **dst, t_env *env)
{
	int		start;
	int		i;
	char	*key;
	char	*val;

	if ((*src)[1] == '?')
	{
		copy_exit_status(dst_idx, src, dst);
		return ;
	}
	start = 1;
	i = *dst_idx;
	while ((*src)[start] && (ft_isalnum((*src)[start]) || (*src)[start] == '_'))
		start++;
	key = ft_substr(*src + 1, 0, start - 1);
	val = get_env_value(key, env);
	if (!val || ft_strchr(val, ' '))
		copy_ambiguous(&i, src, dst, start);
	else
		copy_valid_value(&i, val, dst);
	ft_free(key);
	*src += start;
	*dst_idx = i;
}

int	process_expansion_chars_red(char **src, char **dst, int *j, t_env *env)
{
	if (**src == '\'')
		copy_squoted(j, src, dst);
	else if (**src == '"')
		copy_dquoted(j, src, dst, env);
	else
	{
		if (process_red(src, dst, j, env) == -1)
			return (-1);
	}
	return (0);
}
