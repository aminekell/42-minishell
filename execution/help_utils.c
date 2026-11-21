/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:48:59 by zaissi            #+#    #+#             */
/*   Updated: 2025/07/12 23:26:42 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_help	*help_init(t_list *list, t_export **ptr)
{
	t_help	*help;

	help = ft_malloc(sizeof(t_help));
	if (!help)
		return (NULL);
	help->bonus_type = 0;
	help->list = get_wirdcart(&list);
	if (get_wirdcart_red(&help->list->redirections) && !list->tokens
		&& !list->tokens[0])
	{
		write(2, "MiniShell: ", 12);
		ft_putstr_fd(help->list->redirections->filename, 2);
		write(2, ": ambiguous redirect\n", 22);
		return (NULL);
	}
	help->exp = ptr;
	help->main_pipe[0] = -1;
	help->main_pipe[1] = -1;
	help->prev_pipe[0] = -1;
	help->prev_pipe[1] = -1;
	help->status = 0;
	help->pid = 0;
	help->fd = -1;
	return (help);
}

int	bonus_part(t_list *list, int *status, int stop)
{
	if (stop == 1)
	{
		if (list->type == TYPE_AND)
			if (WIFEXITED(*status) && WEXITSTATUS(*status) != 0)
				return (-1);
	}
	if (stop == 2)
	{
		if (list->type == TYPE_OR)
			if (WIFEXITED(*status) && WEXITSTATUS(*status) == 0)
				return (-1);
	}
	return (0);
}

int	num_value(char **str)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (ft_strcmp(str[i], "*"))
			len++;
		i++;
	}
	return (len);
}

int	get_len_dir(void)
{
	struct dirent	*enty;
	int				len;
	DIR				*dir;

	len = 0;
	dir = opendir(".");
	if (!dir)
		return (0);
	enty = readdir(dir);
	while (enty)
	{
		len++;
		enty = readdir(dir);
	}
	closedir(dir);
	return (len);
}

int	mutche_filename(char *pater, char *filename)
{
	if (*pater == '\0')
		return (*filename == '\0');
	if (*pater == '*')
		return (mutche_filename(pater + 1, filename)
			|| (*filename && mutche_filename(pater, filename + 1)));
	if (*pater == *filename)
		return (mutche_filename(pater + 1, filename + 1));
	return (0);
}
