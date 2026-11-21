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

void	**get_allocs_array(void)
{
	static void	*allocs[MAX_TRACKED_ALLOCS];

	return (allocs);
}

size_t	*get_alloc_count(void)
{
	static size_t	count = 0;

	return (&count);
}

void	*ft_malloc(size_t size)
{
	void	*ptr;
	size_t	*count;
	void	**allocs;

	ptr = malloc(size);
	if (!ptr)
	{
		perror("MiniShell: malloc");
		ft_exit(EXIT_FAILURE);
	}
	count = get_alloc_count();
	allocs = get_allocs_array();
	if (*count < MAX_TRACKED_ALLOCS)
		allocs[(*count)++] = ptr;
	else
	{
		free(ptr);
		ft_putstr_fd("MiniShell: maximum tracked allocations reached\n", 2);
		return (NULL);
	}
	return (ptr);
}

void	ft_free(void *ptr)
{
	size_t	*count;
	void	**allocs;
	size_t	i;

	if (!ptr)
		return ;
	count = get_alloc_count();
	allocs = get_allocs_array();
	i = 0;
	while (i < *count)
	{
		if (allocs[i] == ptr)
		{
			free(ptr);
			allocs[i] = allocs[*count - 1];
			(*count)--;
			return ;
		}
		i++;
	}
	free(ptr);
}

void	free_all(void)
{
	size_t	*count;
	void	**allocs;
	size_t	i;

	count = get_alloc_count();
	allocs = get_allocs_array();
	i = 0;
	while (i < *count)
	{
		free(allocs[i]);
		i++;
	}
	*count = 0;
}
