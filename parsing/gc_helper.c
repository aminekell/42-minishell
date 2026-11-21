/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 05:35:52 by akella            #+#    #+#             */
/*   Updated: 2025/07/07 21:15:35 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	closeall(void)
{
	int	i;
	long	max_fd;

	max_fd = sysconf(_SC_OPEN_MAX);
	i = 3;
	while (i < max_fd)
	{
		close(i);
		i++;
	}
}

void	ft_exit(int status)
{
	free_all();
	closeall();
	exit(status);
}
