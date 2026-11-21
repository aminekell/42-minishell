/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 03:04:29 by akella            #+#    #+#             */
/*   Updated: 2025/07/02 11:06:17 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax_checks.h"

int	ft_syntax_error(void)
{
	ft_putendl_fd("syntax error", 2);
	return (exit_status(1, 258), 1);
}

int	check_unclosed_quotes(char *line)
{
	int		i;
	char	quote_char;
	int		in_quote;

	i = 0;
	in_quote = 0;
	quote_char = 0;
	while (line != NULL && line[i] != '\0')
	{
		if ((line[i] == '\'' || line[i] == '\"') && in_quote == 0)
		{
			in_quote = 1;
			quote_char = line[i];
		}
		else if (in_quote != 0 && line[i] == quote_char)
			in_quote = 0;
		i++;
	}
	if (in_quote != 0)
	{
		ft_syntax_error();
		return (1);
	}
	return (0);
}

int	skip_whitespace(char *line, int start, int len)
{
	int	j;

	j = start;
	while (j < len && (line[j] == ' ' || line[j] == '\t'))
		j++;
	return (j);
}

int	check_pipe_syntax(char *line, int i, int len)
{
	int	j;
	int	k;

	k = 0;
	while (k < i && (line[k] == ' ' || line[k] == '\t'))
		k++;
	if (k == i)
		return (ft_syntax_error());
	j = skip_whitespace(line, i + 1, len);
	if (j == len || line[j] == '|' || line[j] == '&')
		return (ft_syntax_error());
	return (0);
}

int	check_ampersand_syntax(char *line, int i, int len)
{
	int	j;

	if (i + 1 >= len || line[i + 1] != '&')
		return (ft_syntax_error());
	if (i == 0)
		return (ft_syntax_error());
	j = skip_whitespace(line, i + 2, len);
	if (j == len || line[j] == '|' || line[j] == '&')
		return (ft_syntax_error());
	return (0);
}
