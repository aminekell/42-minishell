/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 01:30:23 by akella            #+#    #+#             */
/*   Updated: 2025/07/02 15:31:31 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	count_parts(char **parts)
{
	int	count;

	count = 0;
	while (parts[count])
		count++;
	return (count);
}

static void	copy_tokens_before(char **new_toks, char **tokens, int j)
{
	int	idx;

	idx = 0;
	while (idx < j)
	{
		new_toks[idx] = tokens[idx];
		idx++;
	}
}

static void	copy_parts(char **new_toks, char **parts, int j, int pcount)
{
	int	idx;

	idx = 0;
	while (idx < pcount)
	{
		new_toks[j + idx] = parts[idx];
		idx++;
	}
}

char	**create_new_token_array(char **tokens, int count, int j, char **parts)
{
	char	**new_toks;
	int		pcount;

	pcount = count_parts(parts);
	new_toks = ft_calloc(count + pcount + 1, sizeof(*new_toks));
	if (!new_toks)
		return (NULL);
	copy_tokens_before(new_toks, tokens, j);
	copy_parts(new_toks, parts, j, pcount);
	ft_memmove(&new_toks[j + pcount], &tokens[j + 1],
		(count - j) * sizeof(*tokens));
	new_toks[count + pcount] = NULL;
	return (new_toks);
}

int	is_dollar_inside_double_quotes(const char *s)
{
	int	in_dquote;

	in_dquote = 0;
	while (*s)
	{
		if (*s == '"')
			in_dquote = !in_dquote;
		else if (*s == '$' && in_dquote)
			return (1);
		s++;
	}
	return (0);
}
