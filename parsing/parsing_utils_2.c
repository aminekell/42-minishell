/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 20:05:37 by akella            #+#    #+#             */
/*   Updated: 2025/07/02 11:20:04 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	setup_word_split_arrays(t_token_params *params, char ***parts,
		char ***new_toks, int *pcount)
{
	*parts = ft_split(params->node->tokens[*params->j], ' ');
	if (!*parts)
		return (-1);
	*pcount = 0;
	while ((*parts)[*pcount])
		(*pcount)++;
	*new_toks = ft_calloc(*params->count + *pcount + 1, sizeof(**new_toks));
	if (!*new_toks)
	{
		ft_free_split(*parts);
		return (-1);
	}
	return (0);
}

void	copy_word_split_tokens(t_token_params *params, char **new_toks,
		char **parts, int pcount)
{
	int	idx;

	idx = 0;
	while (idx < *params->j)
	{
		new_toks[idx] = params->node->tokens[idx];
		idx++;
	}
	idx = 0;
	while (idx < pcount)
	{
		new_toks[*params->j + idx] = parts[idx];
		idx++;
	}
	idx = *params->j + 1;
	while (idx < *params->count)
	{
		new_toks[*params->j + pcount + (idx - *params->j - 1)]
			= params->node->tokens[idx];
		idx++;
	}
}
