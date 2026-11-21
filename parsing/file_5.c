/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:35:01 by akella            #+#    #+#             */
/*   Updated: 2025/07/10 22:40:15 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_quoted_assignment(t_expansion_data *exp_data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (exp_data->orig[i])
	{
		if (exp_data->orig[i] == '=' && (exp_data->orig[i + 1] == '"'
				|| exp_data->orig[i + 1] == '\''))
			j = 1;
		i++;
	}
	return (j);
}

int	handle_token_splitting(t_token_manager *token_mgr,
				t_expansion_data *exp_data, int j)
{
	int	split_count;

	(void)j;
	split_count = handle_expansion_split(
			token_mgr->tokens,
			token_mgr->count,
			*(token_mgr->j),
			exp_data->exp);
	if (split_count < 0)
		return (-1);
	*(token_mgr->j) += split_count;
	free(exp_data->orig);
	free(exp_data->exp);
	return (0);
}

int	assign_expanded_token(t_token_manager *token_mgr,
				t_expansion_data *exp_data)
{
	(*(token_mgr->tokens))[*(token_mgr->j)] = exp_data->exp;
	free(exp_data->orig);
	(*(token_mgr->j))++;
	return (0);
}

int	ambigios(int should_update, int new_status)
{
	static int	new;

	if (should_update)
		new = new_status;
	return (new);
}
