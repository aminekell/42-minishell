/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 22:07:46 by akella            #+#    #+#             */
/*   Updated: 2025/07/02 12:39:25 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax_checks.h"

int	check_pipe_start_end(char *line, int i)
{
	int	j;
	int	len;

	if (i == 0)
		return (ft_syntax_error());
	len = ft_strlen(line);
	j = i + 1;
	while (line[j] == ' ' || line[j] == '\t')
		j++;
	if (j >= len || line[j] == '|' || line[j] == '&')
		return (ft_syntax_error());
	return (0);
}

int	ft_check_pipes(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] == '|' && check_pipe_start_end(line, i))
			return (1);
		i++;
	}
	return (0);
}
