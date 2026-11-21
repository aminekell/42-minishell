/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 02:16:13 by akella            #+#    #+#             */
/*   Updated: 2025/07/02 11:02:37 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_type(char *line)
{
	if (!*line)
		return (TYPE_END);
	if (*line == '|')
		return (TYPE_PIPE);
	if (*line == '>' && *(line + 1) == '>')
		return (TYPE_APPEND);
	if (*line == '>')
		return (TYPE_TRUNC);
	if (*line == '<' && *(line + 1) == '<')
		return (TYPE_HEREDOC);
	if (*line == '<')
		return (TYPE_INPUT);
	return (TYPE_END);
}
