/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 19:52:34 by zaissi            #+#    #+#             */
/*   Updated: 2025/07/10 20:20:11 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exe_env(t_list *list)
{
	t_env	*temp;

	if (ft_tokenlen(list->tokens) != 1)
		return (1);
	temp = list->env;
	while (temp)
	{
		printf("%s\n", temp->value);
		temp = temp->next;
	}
	return (0);
}

int	ft_commands_one(t_help *help)
{
	if (!ft_strcmp(help->list->tokens[0], "cd"))
	{
		if (exe_cd(help->list->tokens, &help->list->env, help->exp))
			print_err(3, "cd");
		return (0);
	}
	if (!ft_strcmp(help->list->tokens[0], "pwd"))
	{
		if (exe_pwd(help->list->env))
			print_err(3, "pwd");
		return (0);
	}
	if (!ft_strcmp(help->list->tokens[0], "env"))
	{
		if (exe_env(help->list))
		{
			write(2, "error\n", 7);
			exit_status(1, 1);
		}
		return (0);
	}
	if (!ft_strcmp(help->list->tokens[0], "echo"))
		return (exe_echo(help->list->tokens), 0);
	return (1);
}

int	ft_commands(t_help	*help)
{
	if (!ft_commands_one(help))
		return (0);
	if (!ft_strcmp(help->list->tokens[0], "export"))
	{
		if (exe_export(help->list->tokens, &help->list->env, help->exp))
		{
			write(2, "minishell: export: not a valid identifier\n", 43);
			exit_status(1, 1);
		}
		return (0);
	}
	if (!ft_strcmp(help->list->tokens[0], "unset"))
	{
		if (exe_unset(help->list->tokens, &help->list->env, help->exp))
		{
			write(2, "MiniShell: unset: bad option!!!\n", 33);
			exit_status(1, 1);
		}
		return (0);
	}
	if (!ft_strcmp(help->list->tokens[0], "exit"))
		if (exe_exit(help->list->tokens, help))
			return (exit_status(1, 1), 0);
	return (1);
}

int	print_err(int status, char *str)
{
	if (str && status != 0)
	{
		write(2, "Minishell: ", 12);
		ft_putstr_fd(str, 2);
	}
	if (status == 3 && str != NULL)
	{
		write(2, ": No such file or directory\n", 29);
		exit_status(1, 1);
	}
	if (status == 2 && str != NULL)
	{
		write(2, ": command not found\n", 21);
		exit(127);
	}
	if (status == EISDIR && str != NULL)
	{
		write(2, ": Is a directory\n", 18);
		exit(126);
	}
	return (status);
}

int	parsing_cmd(char *cmd)
{
	if (!cmd || !*cmd)
		return (0);
	if (cmd[ft_strlen(cmd) - 1] == '/' || cmd[ft_strlen(cmd) - 1] == '.')
		return (1);
	return (0);
}
