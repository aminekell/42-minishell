/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:44:44 by akella            #+#    #+#             */
/*   Updated: 2025/07/10 18:03:11 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quotes.h"

int	is_inside_quotes(char *s, int index)
{
	int	in_squote;
	int	in_dquote;
	int	i;

	in_squote = 0;
	in_dquote = 0;
	i = 0;
	while (i < index && s[i])
	{
		if (s[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (s[i] == '\"' && !in_squote)
			in_dquote = !in_dquote;
		i++;
	}
	return (in_squote || in_dquote);
}

int	init_argv(t_list *cmd, char *line)
{
	int	i;

	i = 0;
	while (i < cmd->size && line[i])
	{
		cmd->argv[i] = line[i];
		i++;
	}
	cmd->argv[i] = '\0';
	return (i);
}

void	free_redirections(t_redir **head)
{
	t_redir	*tmp;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->filename);
		free(tmp);
	}
}

char	*extract_filename(char *line, int *idx, t_env *env)
{
	int		start;
	int		end;
	char	*raw;
	char	*expanded;

	start = *idx;
	end = filename_end(line, start);
	if (end == start)
		return (*idx = end, NULL);
	raw = ft_substr(line, start, end - start);
	if (!raw)
		return (NULL);
	expanded = build_expanded_red(raw, env);
	free(raw);
	if (!expanded)
		return (NULL);
	return (handle_expanded_filename(expanded, idx, end));
}

char	*process_quotes_filename(char *raw, int *idx, int end)
{
	char			*result;
	t_quote_helper	h;

	result = ft_calloc(ft_strlen(raw) + 1, sizeof(char));
	if (!result)
	{
		free(raw);
		return (NULL);
	}
	h = (t_quote_helper){raw, result, 0, 0, ft_strlen(raw)};
	result = process_quotes_helper(&h);
	free(raw);
	*idx = end;
	return (result);
}
