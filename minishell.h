/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 22:25:51 by akella            #+#    #+#             */
/*   Updated: 2025/07/12 18:47:48 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/stat.h>
# include "parsing/parsing.h"
# include <termios.h>
# include <limits.h>
# include <errno.h>

typedef struct s_list	t_list;
typedef struct s_env	t_env;
typedef struct s_redir	t_redir;
typedef struct s_export	t_export;

typedef struct s_export
{
	char			*value;
	struct s_export	*next;
}	t_export;

typedef struct s_help
{
	t_list				*list;
	t_export			**exp;
	int					main_pipe[2];
	int					prev_pipe[2];
	int					bonus_type;
	int					status;
	int					pid;
	int					first;
	int					fd;
	struct termios		original_term;
}	t_help;

void		sort_env_to_export_by_value(t_env *env);
void		exe_equal(char *str, t_env **env, t_export **head);
void		unset_export(char *str, t_export **env);
void		error_exit(char *str);
int64_t		exit_atoi(char *str);
t_export	*get_new_value(char *str);
t_env		*creat_env(char **env);
t_env		*get_env_list(char *env);
t_env		*get_new_env(t_env **env, char *path);
t_env		*update_env(char *key, t_env *ptr);
char		**env_return(t_env *env);
int			exe_env(t_list *list);
char		*ft_getenv(t_env *env, char *str);
char		*get_dir_value(char	**token, t_env *env, t_export **ptr);
void		add_to_data(t_env *env, char *str);
void		edit_env_values(char *str, t_env *env);
void		allocat_data(char *str, t_env *env, char *new_data);
int			is_key(char *str, t_env *env);
int			edit_env(char *str, t_env **env, t_export **head);
void		add_new_env(char *str, t_env **env);
int			execute_heredoc(t_list *list, t_help *help);
void		execute_list(t_help *help);
void		execute_command(t_list *list, t_export **ptr);
int			exe(t_help *help);
int			exe_cd(char **v, t_env **env_list, t_export **ptr);
int			exe_echo(char **args);
int			exe_export(char **args, t_env **env, t_export **head);
int			exe_pwd(t_env *env);
int			exe_unset(char **args, t_env **env, t_export **ptr);
char		*return_cmd(char **token, t_env *env);
int			in_export(char *str, t_export *ptr);
int			ft_list_size(t_list *list);
void		free_env(t_env *env);
int			exe_exit(char **args, t_help *help);
void		exe_files(t_help *help);
int			ft_commands(t_help *help);
int			ft_get_file(char *file, int type);
int			get_file_with_path(char *file, int type);
int			execute_redirection(t_redir *redirection, int fd[2], t_help *help);
int			heredoc(char *str, t_env *env, t_help *help);
char		*ft_path(char *str, char *cmd);
int			ft_parser(t_list **list, char **line, t_env *env);
int			parsing_cmd(char *cmd);
char		*build_expanded(const char *str, t_env *env);
int			expanded_length(const char *str, int *flag, t_env *env);
int			ft_len_var(const char *s, int *i, int *flag, t_env *env);
void		insert_exit_status(char **dst, char *status,
				int *dst_idx, char **src);
void		copy_dquoted(int *dst_idx, char **src, char **dst, t_env *env);
void		copy_var(int *dst_idx, char **src, char **dst, t_env *env);

int			mutche_filename(char *pater, char *filename);
void		slash_token(struct dirent *enty, char *token,
				char **new, int *size);
void		regular_token(struct dirent *enty, char *token,
				char **new, int *size);
int			expand_token_array(t_list *node, int i, char **str);
int			token_wildcard(char **token, int *pos, char **str);
char		*update_str(char *str);
int			total_wird(int total, char *str);
void		command_tokens(t_list *node);
char		**wirdcart(char **str, int i);
char		*skip_all_wird(char *str);
int			count_total_entries(char **token);

int			wildcard_token(char *token, char **new, int *size, int *old);

int			get_size(char **token, char **str, int i);
void		later_token(char *token, char **str, char **filter, int *size);
int			get_size_len(char *str);
char		*push_to_ptr(char *str, char *ptr, int len);
t_list		*get_wirdcart(t_list **list);
int			get_wirdcart_red(t_redir **red);
void		ft_free(void *ptr);
t_help		*help_init(t_list *list, t_export **ptr);
void		free_help(t_help *help);
void		check_fd(int fd, char *str);
int			print_err(int status, char *str);
int			is_equl(char *str);
char		*data(char *str);
char		*get_key(char *str);
void		delete_export(t_export **ptr, char *str);
void		wait_command_to_finish(int pids[1024], int max, t_help *help);
int			creat_process(t_help *help);
int			bonus_part(t_list *list, int *status, int stop);
void		child_process(t_help *help);
int			parint_process(t_help *help);
int			befor_exe(t_help *help);
void		child_signel(t_help *help);
void		restore_parent_signals(t_help *help);
int			ft_isdigit(int c);
size_t		ft_tokenlen(char **token);
int			ft_strcmp(const char *s1, const char *s2);
void		ft_exit(int flag);
void		*ft_malloc(size_t size);
char		**ft_split(const char *s, char c);
char		**ft_split_minishell(char *s, char c);
char		**ft_malloc_error(char **arr);
void		ft_exite(t_list **list, t_list **new, char *line);
int			ft_isspace(int c);
int			get_equal(char *str);
int			ft_strncmp(char *s1, char *s2, int n);
int			key_len(char *str);
int			ft_check(t_redir *ptr);
void		closeall(void);
char		*ft_replace_env(char *str, t_env *env);
int			ft_strlcpy_without_term(char *dest, char *src);
void		*ft_malloc(size_t size);
void		ft_free(void *ptr);
void		free_all(void);
void		setup_signals(void);
char		*build_expanded_heredoc(const char *str, t_env *env);
int			process_expansion_chars_red(char **src, char **dst, int *j,
				t_env *env);
char		*build_expanded_red(const char *str, t_env *env);
void		ambigios_check(char *str);

#endif