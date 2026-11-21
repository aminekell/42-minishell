/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:38:31 by zaissi            #+#    #+#             */
/*   Updated: 2025/07/12 18:48:46 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	bypass_flag(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[i])
		return (1);
	if (str[i] && str[i] != '-')
		return (1);
	if (str[i] == '-' && str[i + 1] == '\0')
		return (1);
	i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	exe_echo(char **args)
{
	int	i;
	int	flag;

	(1) && (i = 1, flag = 0);
	if (args[i])
	{
		while (!ft_strcmp(args[i], "-n"))
		{
			flag = 1;
			i++;
		}
		while (!bypass_flag(args[i]))
			(1) && (i++, flag = 1);
		while (args[i])
		{
			if (args[i + 1])
				printf("%s ", args[i]);
			else
				printf("%s", args[i]);
			i++;
		}
	}
	if (!flag)
		printf("\n");
	return (0);
}

int	check_is_nmb(char **str)
{
	int	i;
	int	j;

	i = 1;
	while (str[i])
	{
		j = 0;
		if (i > 1)
			return (200);
		exit_atoi(str[i]);
		i++;
	}
	return (i);
}

int	exe_exit(char **args, t_help *help)
{
	long	i;

	i = 1;
	if (isatty(0) && help->list->type != TYPE_PIPE && help->first)
		write(2, "exit\n", 5);
	if (!ft_strcmp(args[1], "\0"))
		error_exit(args[1]);
	if (!args[1])
		exit(exit_quite(0, 0));
	else
	{
		if (check_is_nmb(args) > 2)
		{
			write(2, "MiniShell: exit: too many args\n", 32);
			return (1);
		}
		else
			exit(exit_atoi(args[1]));
	}
}
