/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 21:26:44 by akella            #+#    #+#             */
/*   Updated: 2025/07/14 22:36:21 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	max_heredoc(int should_update, int new_status)
{
	static int	count = 0;

	if (should_update)
		count = new_status;
	return (count);
}

void	type_2(int type)
{
	int	current_count;

	if (type == 2)
	{
		current_count = max_heredoc(0, 0);
		current_count++;
		max_heredoc(1, current_count);
		if (current_count > 16)
		{
			ft_putendl_fd("Minishell: maximum here-document count exceeded", 2);
			exit(2);
		}
	}
}
