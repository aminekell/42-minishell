/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 21:41:58 by zaissi            #+#    #+#             */
/*   Updated: 2025/07/10 19:29:35 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	parcing(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (1);
	while (str[i] && str[i] != '=' && !(str[i] == '+' && str[i + 1] == '='))
	{
		if (i == 0 && !(ft_isalpha(str[i]) || str[i] == '_'))
			return (1);
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (1);
		i++;
	}
	if (str[i] == '+' && str[i + 1] == '=')
		return (0);
	if (str[i] == '=' && i == 0)
		return (1);
	return (0);
}

int	not_key(char *str, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(str, env->key))
			return (1);
		if (!ft_strcmp(str, env->value))
			return (1);
		env = env->next;
	}
	return (0);
}

int	without_args(t_env *ptr, t_export **head)
{
	t_export	*exp;

	sort_env_to_export_by_value(ptr);
	if (head == NULL || (*head) == NULL)
		return (0);
	exp = *head;
	while (exp)
	{
		printf("declare -x %s\n", exp->value);
		exp = exp->next;
	}
	return (0);
}

void	exe_equal(char *str, t_env **env, t_export **head)
{
	t_export	*exp;
	t_export	*tmp;

	tmp = NULL;
	if (is_equl(str) && ft_strncmp(str, "_=", 2))
	{
		if (!edit_env(str, env, head))
			;
		else
			add_new_env(str, env);
	}
	else if (!in_export(str, *head))
	{
		tmp = *head;
		exp = get_new_value(str);
		if (!tmp)
			*head = exp;
		else
		{
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = exp;
		}
	}
}

int	exe_export(char **args, t_env **env, t_export **head)
{
	t_env	*ptr;
	int		k;
	int		check;

	(1) && (ptr = *env, k = 1, check = 0);
	if (!args[1])
		return (without_args(ptr, head));
	while (args[k])
	{
		if (not_key(args[k], ptr))
		{
			k++;
			continue ;
		}
		if (parcing(args[k]) || ft_isdigit(args[k][0]))
		{
			(1) && (check = 1, k++);
			continue ;
		}
		exe_equal(args[k], &ptr, head);
		(1) && (ptr = *env, k++);
	}
	if (check)
		return (1);
	return (0);
}
