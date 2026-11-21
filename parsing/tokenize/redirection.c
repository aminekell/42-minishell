/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:01:05 by akella            #+#    #+#             */
/*   Updated: 2025/07/12 23:38:52 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quotes.h"

void	reverse_redir_list(t_redir **head)
{
	t_redir	*prev;
	t_redir	*current;
	t_redir	*next;

	prev = NULL;
	current = *head;
	while (current)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*head = prev;
}

int	handle_redirection(t_redir_params *params)
{
	int	i;

	i = 0;
	while (params->cmd->argv[i])
	{
		if (params->cmd->argv[i] == '<' || params->cmd->argv[i] == '>')
		{
			if (parse_redir(params, &i) == -1)
				return (-1);
		}
		else
			i++;
	}
	return (0);
}

int	get_redirection_type(char *argv, int *i, int *adv)
{
	int	type;

	if (argv[*i] == '<')
		type = 0;
	else
		type = 1;
	*adv = 1;
	if (argv[*i + 1] == argv[*i])
	{
		type += 2;
		*adv = 2;
	}
	type_2(type);
	return (type);
}

static char	*get_filename(t_redir_params *params, int type, int *i)
{
	char	*fn;

	if (type == 2)
		fn = extract_filename_no_expand(params->cmd->argv, i);
	else
		fn = extract_filename(params->cmd->argv, i, params->env);
	return (fn);
}

int	parse_redir(t_redir_params *params, int *i)
{
	int		type;
	int		adv;
	char	*fn;

	type = get_redirection_type(params->cmd->argv, i, &adv);
	*i += adv;
	while (params->cmd->argv[*i] == ' ' || params->cmd->argv[*i] == '\t')
		(*i)++;
	if (is_inside_quotes(params->line, *i))
		return (1);
	fn = get_filename(params, type, i);
	if (!fn)
		return (-1);
	if (!add_redirection(params->r, type, fn))
	{
		free(fn);
		free_redirections(params->r);
		ft_exite(params->list, &params->cmd, params->line);
		return (-1);
	}
	return (0);
}
