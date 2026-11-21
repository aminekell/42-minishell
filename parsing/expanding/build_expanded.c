/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_expanded.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 08:08:23 by akella            #+#    #+#             */
/*   Updated: 2025/07/10 17:50:29 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expande.h"

void	handle_exit_statu(char **src, char **dst, int *j)
{
	char	*ret_str;

	ret_str = ft_itoa(exit_status(0, 0));
	if (ret_str)
		insert_exit_status(dst, ret_str, j, src);
	free(ret_str);
}

int	process_expansion_chars_extra(char **src,
			char **dst, int *j, t_env *env)
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
			copy_var(j, src, dst, env);
	}
	else
		(*dst)[(*j)++] = *(*src)++;
	return (0);
}

static int	process_expansion_chars(char **src, char **dst, int *j, t_env *env)
{
	if (**src == '\'')
		copy_squoted(j, src, dst);
	else if (**src == '"')
		copy_dquoted(j, src, dst, env);
	else
		if (process_expansion_chars_extra(src, dst, j, env) == -1)
			return (-1);
	return (0);
}

char	*build_expanded(const char *str, t_env *env)
{
	int		j;
	int		flag;
	int		len;
	char	*dst;
	char	*src;

	j = 0;
	flag = 0;
	len = expanded_length(str, &flag, env);
	if (len == -1)
		return (NULL);
	dst = ft_malloc(len + 1);
	src = (char *)str;
	while (*src)
	{
		if (process_expansion_chars(&src, &dst, &j, env) == -1)
			return (NULL);
	}
	dst[j] = '\0';
	return (dst);
}
