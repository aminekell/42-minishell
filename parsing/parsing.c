/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 12:18:23 by akella            #+#    #+#             */
/*   Updated: 2025/07/12 23:37:25 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	handle_token_creation(t_list **list, char *input,
				t_env *env_c, int i)
{
	t_list	*new_node;
	int		processed;

	new_node = ft_malloc(sizeof(t_list));
	if (!new_node)
	{
		ft_lstclear(list);
		return (-1);
	}
	if (!init_token_node(list, &new_node, input + i, env_c))
	{
		free(new_node);
		ft_lstclear(list);
		return (-1);
	}
	processed = process_new_token(list, new_node, &input[i], env_c);
	if (processed <= 0)
	{
		ft_lstclear(list);
		return (-1);
	}
	return (processed);
}

void	ambigios_check(char *str)
{
	if (ambigios(0, 0) == 1 && str[0] == '$')
	{
		write(2, "MiniShell: ", 12);
		ft_putstr_fd(str, 2);
		write(2, ": ambiguous redirect\n", 22);
		ambigios(1, 0);
		exit(1);
	}
}

int	process_token_loop(t_list **list, char *temp, t_env *env_c)
{
	int		i;
	int		processed;
	size_t	input_len;

	i = 0;
	input_len = ft_strlen(temp);
	while (i < (int)input_len)
	{
		processed = handle_token_creation(list, temp, env_c, i);
		if (processed == -1)
			return (-1);
		i += processed;
		if (temp[i] && !ft_isspace((unsigned char)temp[i]))
			i++;
	}
	return (i);
}
