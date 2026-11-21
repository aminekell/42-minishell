/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:31:58 by zaissi            #+#    #+#             */
/*   Updated: 2025/07/10 19:31:26 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	insert_sorted_export(t_export **head, t_export *new_node)
{
	t_export	*curr;
	t_export	*prev;

	if (!*head || ft_strcmp(new_node->value, (*head)->value) < 0)
	{
		new_node->next = *head;
		*head = new_node;
		return ;
	}
	prev = *head;
	curr = (*head)->next;
	while (curr && ft_strcmp(new_node->value, curr->value) > 0)
	{
		prev = curr;
		curr = curr->next;
	}
	new_node->next = curr;
	prev->next = new_node;
}

void	print_sorted_free(t_export *ptr)
{
	while (ptr)
	{
		printf("declare -x %s\n", ptr->value);
		ptr = ptr->next;
	}
}

void	sort_env_to_export_by_value(t_env *env)
{
	t_export	*sorted;
	t_export	*new;
	char		*str;
	char		*var;

	sorted = NULL;
	while (env)
	{
		if (env->value && ft_strcmp(env->key, "_"))
		{
			new = ft_malloc(sizeof(t_export));
			str = ft_strjoin("\"", env->data);
			var = ft_strjoin(str, "\"");
			ft_free(str);
			str = ft_strjoin(env->key, "=");
			new->value = ft_strjoin(str, var);
			ft_free(str);
			ft_free(var);
			new->next = NULL;
			insert_sorted_export(&sorted, new);
		}
		env = env->next;
	}
	print_sorted_free(sorted);
}
