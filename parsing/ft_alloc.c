/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:33:03 by akella            #+#    #+#             */
/*   Updated: 2025/07/07 20:09:50 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdint.h>

static void		**g_allocs;
static size_t	g_alloc_count;
static size_t	g_alloc_capacity;

static void	grow_allocs(void)
{
	void	**allocs;
	size_t	capacity;

	capacity = 64;
	if (g_alloc_capacity)
	{
		if (g_alloc_capacity > SIZE_MAX / 2 / sizeof(*allocs))
			ft_exit(EXIT_FAILURE);
		capacity = g_alloc_capacity * 2;
	}
	allocs = malloc(capacity * sizeof(*allocs));
	if (!allocs)
	{
		perror("MiniShell: malloc");
		ft_exit(EXIT_FAILURE);
	}
	if (g_alloc_count)
		ft_memcpy(allocs, g_allocs, g_alloc_count * sizeof(*allocs));
	free(g_allocs);
	g_allocs = allocs;
	g_alloc_capacity = capacity;
}

void	*ft_malloc(size_t size)
{
	void	*ptr;

	if (g_alloc_count == g_alloc_capacity)
		grow_allocs();
	ptr = malloc(size);
	if (!ptr)
	{
		perror("MiniShell: malloc");
		ft_exit(EXIT_FAILURE);
	}
	g_allocs[g_alloc_count++] = ptr;
	return (ptr);
}

void	ft_free(void *ptr)
{
	size_t	i;

	if (!ptr)
		return ;
	i = 0;
	while (i < g_alloc_count)
	{
		if (g_allocs[i] == ptr)
		{
			g_allocs[i] = g_allocs[--g_alloc_count];
			break ;
		}
		i++;
	}
	free(ptr);
}

void	free_all(void)
{
	while (g_alloc_count)
		free(g_allocs[--g_alloc_count]);
	free(g_allocs);
	g_allocs = NULL;
	g_alloc_capacity = 0;
}
