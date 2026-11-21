/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:46:04 by akella            #+#    #+#             */
/*   Updated: 2025/07/10 23:46:56 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTES_H
# define QUOTES_H

# include "../../minishell.h"

typedef struct s_list	t_list;
typedef struct s_redir	t_redir;
typedef struct s_env	t_env;

typedef struct s_redir_params
{
	t_list	**list;
	t_list	*cmd;
	char	*line;
	t_redir	**r;
	t_env	*env;
}	t_redir_params;

int		is_inside_quotes(char *s, int index);
int		init_argv(t_list *cmd, char *line);

void	free_redirections(t_redir **head);
int		add_redirection(t_redir **head, int type, char *filename);
void	reverse_redir_list(t_redir **head);
int		handle_redirection(t_redir_params *params);
int		parse_redir(t_redir_params *params, int *i);

char	*extract_filename_no_expand(char *line, int *idx);
int		filename_end(const char *s, int i);
char	*extract_filename(char *line, int *idx, t_env *env);
int		consume_redir(char *s, int i);
void	strip_redirections(char *argv);

int		copy_and_tokenize(t_list **list, t_list *cmd, char *line, t_env *env);
int		filter_tokens(t_list **list, t_list *cmd, char *line);
void	copy_tokens(char **src, char **dst);
int		count_tokens(char **toks);
char	**ft_split_whitespace(char *s);

char	*process_quotes_filename_hc(char *raw, int *idx, int end);
char	*process_quotes_helper_hc(t_quote_helper_hc *h);
void	process_quoted_segment_hc(t_quote_helper_hc *h, char quote);
char	*handle_unexpanded_filename(char *raw, int *idx, int end);

int		process_red(char **src, char **dst, int *j, t_env *env);
void	copy_var_red(int *dst_idx, char **src, char **dst, t_env *env);
char	*build_expanded_red(const char *str, t_env *env);

int		expanded_length(const char *str, int *flag, t_env *env);
char	*build_expanded(const char *str, t_env *env);
int		handle_double_quote(const char *str, int *idx,
			int *expanded, t_env *env);
void	copy_squoted(int *dst_idx, char **src, char **dst);
int		handle_literal_double(const char *str, int *idx, int len);
int		handle_single_quote(const char *str, int *idx, int len);
char	*get_env_value(const char *name, t_env *env);
int		handle_literal_single(const char *str, int *idx, int len);
int		ft_len_var(const char *s, int *i, int *flag, t_env *env);

void	insert_exit_status(char **dst, char *status, int *dst_idx, char **src);
void	copy_literal_single(int *dst_idx, char **src, char **dst);
void	copy_literal_double(int *dst_idx, char **src, char **dst);
void	copy_dquoted(int *dst_idx, char **src, char **dst, t_env *env);
void	copy_exit_status(int *dst_idx, char **src, char **dst);

int		handle_dollar(const char *str, int *pos, int *expanded, t_env *env);
int		is_valid_var_char(char c);
int		is_valid_var_start_char(char c);
int		handle_exit_status(int *pos, int *expanded);
int		handle_var_name(const char *str, int *pos, int *expanded, t_env *env);
void	copy_var(int *dst_idx, char **src, char **dst, t_env *env);

int		process_expansion_chars_extra(char **src,
			char **dst, int *j, t_env *env);
void	handle_exit_statu(char **src, char **dst, int *j);
int		process_expansion_chars_red(char **src, char **dst, int *j, t_env *env);
char	*build_expanded_red(const char *str, t_env *env);

#endif
