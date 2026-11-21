/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 03:02:21 by akella            #+#    #+#             */
/*   Updated: 2025/07/14 22:37:47 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	exit_status(int should_update, int new_status)
{
	static int	new;

	max_heredoc(1, 0);
	exit_quite(1, new);
	if (should_update)
		new = new_status;
	return (new);
}

int	check_print(int should_update, int new_status)
{
	static int	new;

	if (should_update)
		new = new_status;
	return (new);
}

int	empty(int should_update, int new_status)
{
	static int	new;

	if (should_update)
		new = new_status;
	return (new);
}

int	expand(int should_update, int new_status)
{
	static int	new;

	if (should_update)
		new = new_status;
	return (new);
}

int	exit_quite(int update, int n_status)
{
	static int	new;

	if (update)
		new = n_status;
	return (new);
}
