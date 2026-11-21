/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:49:44 by akella            #+#    #+#             */
/*   Updated: 2025/07/07 21:18:33 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	process_token_expan(t_token_manager *token_mgr, t_expansion_data *exp_data)
{
	int		j;
	int		has_quoted_var;
	char	*dollar;

	if (!exp_data->orig)
		return (-1);
	if (ft_strchr(exp_data->orig, '\'') && !ft_strchr(exp_data->orig, '"'))
		return (assign_expanded_token(token_mgr, exp_data));
	j = check_quoted_assignment(exp_data);
	has_quoted_var = 0;
	dollar = ft_strchr(exp_data->orig, '$');
	if (dollar)
	{
		dollar++;
		while (*dollar && (ft_isalnum(*dollar) || *dollar == '_'))
			dollar++;
		if (*dollar == '"' || *dollar == '\'')
			has_quoted_var = 1;
	}
	if (exp_data->exp && !exp_data->had_assign && ft_strchr(exp_data->orig, '$')
		&& ft_strchr(exp_data->exp, ' ') && j == 0
		&& !is_dollar_inside_double_quotes(exp_data->orig) && !has_quoted_var)
		return (handle_token_splitting(token_mgr, exp_data, j));
	return (assign_expanded_token(token_mgr, exp_data));
}

static int	process_and_filter_tokens(char **tokens, int count)
{
	int	write_idx;
	int	i;

	write_idx = 0;
	i = 0;
	while (i < count)
	{
		if (tokens[i] && ft_strlen(tokens[i]) == 0 && empty(0, 0) != 1)
			ft_free(tokens[i]);
		else
			tokens[write_idx++] = tokens[i];
		i++;
	}
	while (write_idx < count)
		tokens[write_idx++] = NULL;
	return (empty(1, 0), 0);
}

int	process_all_tokens(t_list *node, t_env *env)
{
	char	**tokens;
	int		count;
	int		j;

	tokens = node->tokens;
	count = 0;
	while (tokens[count])
		count++;
	j = 0;
	while (j < count)
		process_single_token(&tokens, &count, &j, env);
	node->tokens = tokens;
	return (process_and_filter_tokens(tokens, count));
}

int	process_new_token(t_list **lst, t_list *node, char *line, t_env *env)
{
	int	i;

	i = copy_and_tokenize(lst, node, line, env);
	if (i < 0)
		return (-1);
	if (process_all_tokens(node, env) < 0)
		return (-1);
	node->type = ft_type(line + i);
	if (node->type == TYPE_OR || node->type == TYPE_AND
		|| node->type == TYPE_HEREDOC || node->type == TYPE_APPEND)
		i++;
	ft_lstadd_back(lst, node);
	exit_status(1, 0);
	return (i);
}

int	init_token_node(t_list **list, t_list **new, char *line, t_env *env)
{
	(void)list;
	*new = ft_malloc(sizeof(t_list));
	if (!*new)
		return (0);
	(*new)->env = env;
	(*new)->argv = NULL;
	(*new)->tokens = NULL;
	(*new)->type = TYPE_COMMAND;
	(*new)->size = ft_size(line);
	(*new)->next = NULL;
	if ((*new)->size <= 0)
	{
		free(*new);
		*new = NULL;
		return (0);
	}
	(*new)->argv = ft_malloc(((*new)->size + 1) * sizeof(char *));
	(*new)->tokens = ft_malloc(sizeof(char *));
	return (1);
}
