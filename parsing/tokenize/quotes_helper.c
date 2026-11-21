/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:22:05 by akella            #+#    #+#             */
/*   Updated: 2025/07/03 16:38:32 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quotes.h"

void	process_quoted_segment_hc(t_quote_helper_hc *h, char quote)
{
	h->src++;
	while (h->src < h->len && h->raw[h->src] != quote)
		h->result[h->dst++] = h->raw[h->src++];
	if (h->src < h->len)
		h->src++;
}

char	*process_quotes_helper_hc(t_quote_helper_hc *h)
{
	char	quote;

	while (h->src < h->len)
	{
		if (h->raw[h->src] == '"' || h->raw[h->src] == '\'')
		{
			quote = h->raw[h->src];
			process_quoted_segment_hc(h, quote);
		}
		else
			h->result[h->dst++] = h->raw[h->src++];
	}
	h->result[h->dst] = '\0';
	return (h->result);
}

char	*process_quotes_filename_hc(char *raw, int *idx, int end)
{
	char				*result;
	t_quote_helper_hc	h;

	if (!raw)
		return (NULL);
	result = ft_calloc(ft_strlen(raw) + 1, sizeof(char));
	if (!result)
	{
		free(raw);
		return (NULL);
	}
	h = (t_quote_helper_hc){raw, result, 0, 0, ft_strlen(raw)};
	result = process_quotes_helper_hc(&h);
	free(raw);
	*idx = end;
	return (result);
}

char	*build_expanded_red(const char *str, t_env *env)
{
	int		j;
	int		flag;
	int		len;
	char	*dst;
	char	*src;

	j = 0;
	flag = 0;
	len = expanded_length(str, &flag, env);
	if (len == -1)
		return (NULL);
	dst = ft_malloc(len + 1);
	src = (char *)str;
	while (*src)
	{
		if (process_expansion_chars_red(&src, &dst, &j, env) == -1)
			return (NULL);
	}
	dst[j] = '\0';
	return (dst);
}
