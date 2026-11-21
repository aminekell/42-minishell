/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:20:57 by akella            #+#    #+#             */
/*   Updated: 2025/07/06 16:19:40 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	handle_expansion_split(char ***tokens, int *count, int j, char *exp)
{
	char	**parts;
	char	**new_toks;
	int		pcount;

	if (!tokens || !*tokens || !count || !exp)
		return (-1);
	parts = ft_split(exp, ' ');
	if (!parts)
		return (-1);
	pcount = 0;
	while (parts[pcount])
		pcount++;
	new_toks = create_new_token_array(*tokens, *count, j, parts);
	if (!new_toks)
	{
		free_array(parts);
		return (-1);
	}
	free(*tokens);
	*tokens = new_toks;
	*count = *count + pcount - 1;
	return (pcount);
}

static int	process_expansion(t_expansion_args *args, char *orig,
	char *exp)
{
	t_token_manager		mgr;
	t_expansion_data	data;

	data.had_assign = is_assignment_word(orig);
	data.orig = orig;
	data.exp = exp;
	data.had_assign = data.had_assign;
	mgr.tokens = args->tokens;
	mgr.count = args->count;
	mgr.j = args->j;
	return (process_token_expan(&mgr, &data));
}

int	process_single_token(char ***tokens, int *count, int *j, t_env *env)
{
	t_expansion_args	args;
	char				*orig;
	char				*exp;
	int					result;

	if (!tokens || !*tokens || !count || !j || !env)
		return (-1);
	orig = (*tokens)[*j];
	args.tokens = tokens;
	args.count = count;
	args.j = j;
	args.env = env;
	exp = build_expanded(orig, env);
	result = process_expansion(&args, orig, exp);
	return (result);
}
