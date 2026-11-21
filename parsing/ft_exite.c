/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exite.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 06:20:26 by akella            #+#    #+#             */
/*   Updated: 2025/06/12 22:28:08 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_lstfree(t_list **list)
{
	t_list	*element;
	t_list	*temp;
	int		i;

	element = *list;
	while (element)
	{
		temp = element->next;
		i = 0;
		while (element->tokens[i])
		{
			free(element->tokens[i]);
			i++;
		}
		free(element->tokens);
		free(element);
		element = temp;
	}
	*list = NULL;
}

void	ft_exite(t_list **list, t_list **new, char *line)
{
	if (*new != NULL)
		ft_lstfree(new);
	free(line);
	ft_lstfree(list);
	exit(1);
}
