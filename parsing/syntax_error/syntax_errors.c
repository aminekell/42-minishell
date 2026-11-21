/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:46:42 by akella            #+#    #+#             */
/*   Updated: 2025/07/02 12:38:58 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax_checks.h"

int	check_start(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '|' || line[i] == '&')
		return (ft_syntax_error());
	return (0);
}

int	ft_line_error(char *line)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	if (!line || ft_three_pipe(line))
		return (1);
	if (check_start(line))
		return (1);
	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '"') && quote == 0)
			quote = line[i];
		else if (line[i] == quote)
			quote = 0;
		if (quote)
		{
			i++;
			continue ;
		}
		if (ft_semicolon_and_pipe(line, i))
			return (1);
		i++;
	}
	return (0);
}

int	check_pipe_amp(char *line, int i)
{
	int	j;
	int	len;

	len = ft_strlen(line);
	if (line[i] == '|' && (i + 1 >= len || line[i + 1] != '|'))
	{
		j = i + 1;
		while (line[j] == ' ' || line[j] == '\t')
			j++;
		if (!line[j] || line[j] == '|' || line[j] == '&')
			return (ft_syntax_error());
	}
	if (line[i] == '&' && (i + 1 >= len || line[i + 1] != '&'))
	{
		j = i + 1;
		while (line[j] == ' ' || line[j] == '\t')
			j++;
		if (!line[j] || line[j] == '|' || line[j] == '&')
			return (ft_syntax_error());
	}
	return (0);
}

int	ft_semicolon_and_pipe(char *line, int i)
{
	if (!line)
		return (0);
	if (check_pipe_amp(line, i))
		return (1);
	return (0);
}
