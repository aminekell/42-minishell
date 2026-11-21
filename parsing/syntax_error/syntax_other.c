/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_other.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 20:55:22 by akella            #+#    #+#             */
/*   Updated: 2025/07/02 12:39:15 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax_checks.h"

int	quote_loop(char *line)
{
	int		i;
	char	quote_char;
	int		in_quote;

	i = 0;
	in_quote = 0;
	while (line[i])
	{
		if (!in_quote && (line[i] == '\'' || line[i] == '\"'))
		{
			in_quote = 1;
			quote_char = line[i];
		}
		else if (in_quote && line[i] == quote_char)
			in_quote = 0;
		i++;
	}
	return (in_quote);
}

static int	handle_quote_char(char c, char *quote)
{
	if ((c == '\'' || c == '"') && *quote == 0)
	{
		*quote = c;
		return (1);
	}
	else if (c == *quote)
	{
		*quote = 0;
		return (1);
	}
	return (0);
}

int	check_parentheses(char *line)
{
	int		i;
	int		count;
	char	quote;
	int		last_open;

	i = 0;
	count = 0;
	quote = 0;
	last_open = -1;
	while (line && line[i])
	{
		handle_quote_char(line[i], &quote);
		i++;
	}
	if (count != 0)
		return (ft_syntax_error());
	return (0);
}
