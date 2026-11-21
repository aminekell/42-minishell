/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toknize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 12:42:10 by akella            #+#    #+#             */
/*   Updated: 2025/07/02 19:39:58 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quotes.h"

int	count_tokens(char **toks)
{
	int	n;
	int	i;

	n = 0;
	i = 0;
	while (toks[i])
	{
		if (!(toks[i][0] == '<' || toks[i][0] == '>') || ft_strlen(toks[i]) > 2)
			n++;
		i++;
	}
	return (n);
}

void	copy_tokens(char **src, char **dst)
{
	int	r;
	int	w;

	r = 0;
	w = 0;
	while (src[r])
	{
		if ((src[r][0] == '<' || src[r][0] == '>') && ft_strlen(src[r]) <= 2)
			r += 2;
		else
			dst[w++] = src[r++];
	}
	dst[w] = NULL;
}

int	filter_tokens(t_list **list, t_list *cmd, char *line)
{
	int		nb;
	char	**new_toks;

	nb = count_tokens(cmd->tokens);
	new_toks = ft_malloc((nb + 1) * sizeof(char *));
	if (!new_toks)
	{
		free_redirections(&cmd->redirections);
		ft_exite(list, &cmd, line);
		return (-1);
	}
	copy_tokens(cmd->tokens, new_toks);
	free(cmd->tokens);
	cmd->tokens = new_toks;
	return (0);
}

int	copy_and_tokenize(t_list **list, t_list *cmd, char *line, t_env *env)
{
	int				len;
	t_redir			*redirs;
	t_redir_params	params;

	len = init_argv(cmd, line);
	redirs = NULL;
	params.list = list;
	params.cmd = cmd;
	params.line = line;
	params.r = &redirs;
	params.env = env;
	if (handle_redirection(&params) == -1)
		return (-1);
	reverse_redir_list(&redirs);
	cmd->redirections = redirs;
	strip_redirections(cmd->argv);
	cmd->tokens = ft_split_whitespace(cmd->argv);
	if (!cmd->tokens)
	{
		free_redirections(&redirs);
		return (ft_exite(list, &cmd, line), -1);
	}
	if (filter_tokens(list, cmd, line) == -1)
		return (-1);
	return (len);
}

int	add_redirection(t_redir **head, int type, char *filename)
{
	t_redir	*new_node;

	new_node = ft_malloc(sizeof(t_redir));
	if (!new_node)
		return (0);
	new_node->type = type;
	new_node->filename = filename;
	new_node->next = *head;
	*head = new_node;
	return (1);
}
