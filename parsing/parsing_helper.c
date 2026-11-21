/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 19:24:35 by akella            #+#    #+#             */
/*   Updated: 2025/07/02 11:17:03 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\f' || c == '\v');
}

void	free_token(char **tokens)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

void	ft_lstclear(t_list **lst)
{
	t_list	*current;
	t_list	*next_node;

	if (!lst || !*lst)
		return ;
	current = *lst;
	while (current)
	{
		next_node = current->next;
		if (current->tokens)
			free_token(current->tokens);
		ft_free(current);
		current = next_node;
	}
	*lst = NULL;
}

int	ft_parser(t_list **list, char **line, t_env *env)
{
	char	*temp;
	t_env	*env_c;

	if (!list || !line || !*line)
		return (1);
	if (**line == '\0')
	{
		free(*line);
		*line = NULL;
		return (1);
	}
	add_history(*line);
	temp = *line;
	env_c = env;
	if (check_unclosed_quotes(*line) || ft_check_redirections(*line)
		|| ft_line_error(*line))
		return (free(*line), *line = NULL, 1);
	if (process_token_loop(list, temp, env_c) == -1)
	{
		ft_free(temp);
		*line = NULL;
		return (1);
	}
	free(*line);
	return (*line = NULL, 0);
}
