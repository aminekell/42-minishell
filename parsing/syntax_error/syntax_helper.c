/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:02:56 by akella            #+#    #+#             */
/*   Updated: 2025/07/06 20:26:44 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax_checks.h"

int	validate_redir(char *line, int *idx)
{
	char	type;
	int		count;
	int		j;

	type = line[*idx];
	count = 1;
	j = *idx + 1;
	while (line[j] && line[j] == type)
	{
		count++;
		j++;
	}
	if (count > 2)
		return (ft_syntax_error());
	while (line[j] == ' ' || line[j] == '\t')
		j++;
	if (!line[j] || line[j] == '<' || line[j] == '>'
		|| line[j] == '|')
		return (ft_syntax_error());
	*idx = j;
	return (0);
}

int	ft_check_redirections(char *line)
{
	int	i;
	int	in_single;
	int	in_double;

	if (!line)
		return (0);
	i = 0;
	in_single = 0;
	in_double = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !in_double && (i == 0 || line[i - 1] != '\\'))
			in_single = !in_single;
		else if (line[i] == '"'
			&& !in_single && (i == 0 || line[i - 1] != '\\'))
			in_double = !in_double;
		else if (!in_single && !in_double)
			if ((line[i] == '<' || line[i] == '>') && validate_redir(line, &i))
				return (1);
		i++;
	}
	return (0);
}
