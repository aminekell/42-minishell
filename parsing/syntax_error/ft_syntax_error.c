/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:51:51 by akella            #+#    #+#             */
/*   Updated: 2025/07/02 12:38:36 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax_checks.h"

static int	check_redirection_syntax(char *line, int i, int len)
{
	int	j;

	if (i + 1 < len && line[i + 1] == line[i])
		i++;
	j = skip_whitespace(line, i + 1, len);
	if (j == len || line[j] == '|' || line[j] == '&'
		|| line[j] == '<' || line[j] == '>')
		return (ft_syntax_error());
	return (0);
}

static int	process_character(char *line, int i, int len)
{
	if (line[i] == '|')
	{
		if (check_pipe_syntax(line, i, len))
			return (1);
	}
	else if (line[i] == '&')
	{
		if (check_ampersand_syntax(line, i, len))
			return (1);
		i++;
	}
	else if (line[i] == '<' || line[i] == '>')
	{
		if (check_redirection_syntax(line, i, len))
			return (1);
		if (i + 1 < len && line[i + 1] == line[i])
			i++;
	}
	return (0);
}

static int	process_quotes(char *line, int i, int *in_quote, char *quote_char)
{
	if ((line[i] == '\'' || line[i] == '\"') && *in_quote == 0)
	{
		*in_quote = 1;
		*quote_char = line[i];
	}
	else if (*in_quote && line[i] == *quote_char)
		*in_quote = 0;
	return (0);
}

int	ft_line_error(char *line)
{
	int		i;
	int		len;
	int		in_quote;
	char	quote_char;

	if (!line)
		return (0);
	if (check_unclosed_quotes(line))
		return (1);
	len = ft_strlen(line);
	i = 0;
	in_quote = 0;
	quote_char = 0;
	while (i < len)
	{
		process_quotes(line, i, &in_quote, &quote_char);
		if (!in_quote && process_character(line, i, len))
			return (1);
		i++;
	}
	return (0);
}
