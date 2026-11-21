/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 11:00:04 by zaissi            #+#    #+#             */
/*   Updated: 2025/07/11 14:29:53 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*init_env(char **envp, t_export **ptr)
{
	t_env	*new_env;
	char	*data;
	char	buffer[PATH_MAX];

	if (!isatty(0) || !isatty(1))
		exit(1);
	if (envp && envp[0])
		new_env = creat_env(envp);
	else
	{
		write(2, "MiniShell: Warning: env not SET!!!!\n", 37);
		getcwd(buffer, PATH_MAX);
		new_env = ft_malloc(sizeof(t_env));
		new_env->key = ft_strdup("_");
		new_env->data = ft_strjoin(buffer, "/minishell");
		data = ft_strjoin(new_env->key, "=");
		new_env->value = ft_strjoin(data, new_env->data);
		new_env->ret = -1;
		new_env->next = NULL;
		ft_free(data);
		data = ft_strjoin("PWD=", buffer);
		add_new_env(data, &new_env);
		ft_free(data);
	}
	return (exe_equal("OLDPWD", &new_env, ptr), new_env);
}

int	main(int argc, char *argv[], char **envp)
{
	t_env		*env_list;
	t_list		*list;
	t_export	*ptr;
	char		*line;

	(1) && ((void)argc, (void)argv, ptr = NULL);
	setup_signals();
	if (!isatty(0) || !isatty(1))
		write(2, "MiniShell: the program most be run on tty\n", 43);
	env_list = init_env(envp, &ptr);
	while (1)
	{
		list = NULL;
		line = readline("minishell@1337-> ");
		if (!line)
		{
			write(STDOUT_FILENO, "exit\n", 6);
			break ;
		}
		if (!ft_parser(&list, &line, env_list))
			execute_command(list, &ptr);
		ft_lstclear(&list);
		free(line);
	}
	return (exit_status(0, 0));
}
