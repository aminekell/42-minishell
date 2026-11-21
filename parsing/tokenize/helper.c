/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 03:59:04 by akella            #+#    #+#             */
/*   Updated: 2025/07/02 13:57:48 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quotes.h"

void	process_quoted_segment(t_quote_helper *h, char quote)
{
	h->src++;
	if (quote == '\'' || quote == '"')
		h->result[h->dst++] = quote;
	while (h->src < h->len && h->raw[h->src] != quote)
		h->result[h->dst++] = h->raw[h->src++];
	if (h->src < h->len)
	{
		if (quote == '\'' || quote == '"')
			h->result[h->dst++] = quote;
		h->src++;
	}
}

char	*process_quotes_helper(t_quote_helper *h)
{
	char	quote;

	while (h->src < h->len)
	{
		if (h->raw[h->src] == '"' || h->raw[h->src] == '\'')
		{
			quote = h->raw[h->src];
			process_quoted_segment(h, quote);
		}
		else
			h->result[h->dst++] = h->raw[h->src++];
	}
	h->result[h->dst] = '\0';
	return (h->result);
}

int	process_quoted_filename(char *line, int i, char q)
{
	i++;
	while (line[i] && line[i] != q)
		i++;
	if (line[i] == q)
		i++;
	return (i);
}

int	filename_end(const char *s, int i)
{
	while (s[i] && s[i] != ' ' && s[i] != '<' && s[i] != '>')
	{
		if (s[i] == '"' || s[i] == '\'')
			i = process_quoted_filename((char *)s, i, s[i]);
		else
			i++;
	}
	return (i);
}

char	*handle_expanded_filename(char *expanded, int *idx, int end)
{
	char			*result;
	t_quote_helper	h;

	if (!ft_strchr(expanded, '"') && !ft_strchr(expanded, '\''))
	{
		*idx = end;
		return (expanded);
	}
	result = ft_calloc(ft_strlen(expanded) + 1, sizeof(char));
	if (!result)
	{
		free(expanded);
		return (NULL);
	}
	h = (t_quote_helper){expanded, result, 0, 0, ft_strlen(expanded)};
	result = process_quotes_helper(&h);
	free(expanded);
	*idx = end;
	if (!result || *result == '\0')
	{
		free(result);
		return (NULL);
	}
	return (result);
}
