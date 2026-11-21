/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:07:48 by akella            #+#    #+#             */
/*   Updated: 2025/07/03 16:47:26 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quotes.h"

char	*handle_unexpanded_filename(char *raw, int *idx, int end)
{
	if (!ft_strchr(raw, '"') && !ft_strchr(raw, '\''))
	{
		expand(1, 1);
		*idx = end;
		return (raw);
	}
	expand(1, 0);
	return (process_quotes_filename_hc(raw, idx, end));
}

char	*extract_filename_no_expand(char *line, int *idx)
{
	int		start;
	int		end;
	char	*raw;

	start = *idx;
	end = filename_end(line, start);
	if (end == start)
		return (*idx = end, NULL);
	raw = ft_substr(line, start, end - start);
	if (!raw)
		return (NULL);
	return (handle_unexpanded_filename(raw, idx, end));
}

static int	process_quoted_redir(char *s, int i, char quote)
{
	s[i++] = ' ';
	while (s[i] && s[i] != quote)
		s[i++] = ' ';
	if (s[i] == quote)
		s[i++] = ' ';
	return (i);
}

int	consume_redir(char *s, int i)
{
	char	op;

	op = s[i];
	s[i++] = ' ';
	if (s[i] == op)
		s[i++] = ' ';
	while (s[i] == ' ')
		s[i++] = ' ';
	while (s[i] && s[i] != ' ' && s[i] != '<' && s[i] != '>')
	{
		if (s[i] == '"' || s[i] == '\'')
			i = process_quoted_redir(s, i, s[i]);
		else
			s[i++] = ' ';
	}
	return (i);
}

void	strip_redirections(char *argv)
{
	int		i;
	char	quote;

	i = 0;
	while (argv[i])
	{
		if ((argv[i] == '<' || argv[i] == '>') && !is_inside_quotes(argv, i))
			i = consume_redir(argv, i);
		else if (argv[i] == '"' || argv[i] == '\'')
		{
			quote = argv[i++];
			while (argv[i] && argv[i] != quote)
				i++;
			if (argv[i] == quote)
				i++;
		}
		else
			i++;
	}
}
