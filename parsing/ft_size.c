/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_size.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 21:07:45 by akella            #+#    #+#             */
/*   Updated: 2025/07/02 11:38:29 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_parser_quotes(char *line, int i, char quote)
{
	++i;
	while (line[i] != quote && line[i] != '\0')
		++i;
	return (i);
}

int	ft_handle_quotes(char *line, int *i, int *in_squote, int *in_dquote)
{
	if (line[*i] == '"' && !(*in_squote))
	{
		if (!(*in_dquote))
		{
			*in_dquote = 1;
			*i = ft_parser_quotes(line, *i, '"');
			if (line[*i] == '"')
				*in_dquote = 0;
		}
	}
	else if (line[*i] == '\'' && !(*in_dquote))
	{
		if (!(*in_squote))
		{
			*in_squote = 1;
			*i = ft_parser_quotes(line, *i, '\'');
			if (line[*i] == '\'')
				*in_squote = 0;
		}
	}
	return (0);
}

int	ft_size(char *line)
{
	int	i;
	int	in_squote;
	int	in_dquote;

	i = 0;
	in_squote = 0;
	in_dquote = 0;
	while (line[i])
	{
		ft_handle_quotes(line, &i, &in_squote, &in_dquote);
		if ((line[i] == '|') && !in_squote && !in_dquote)
		{
			if (i == 0)
				return (1);
			return (i);
		}
		++i;
	}
	return (i);
}
