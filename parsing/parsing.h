/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 21:26:02 by akella            #+#    #+#             */
/*   Updated: 2025/07/10 21:54:10 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../minishell.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include <stdio.h>
# include <signal.h>
# include <limits.h>
# include <termios.h>
# include "syntax_error/syntax_checks.h"

# define INPUT			0
# define NOT_FOUND		-1
# define OUTPUT			1
# define STDERR			2
# define TYPE_END		3
# define TYPE_PIPE		4
# define TYPE_BREAK		5
# define TYPE_TRUNC		6
# define TYPE_APPEND	7
# define TYPE_INPUT		8
# define TYPE_HEREDOC	9
# define TYPE_OR		10
# define TYPE_AND		11
# define TYPE_COMMAND	12

typedef struct s_redir
{
	int				type;
	char			*filename;
	struct s_redir	*next;
}					t_redir;

typedef struct s_env
{
	char			*value;
	char			*data;
	char			*key;
	int				ret;
	struct s_env	*next;
}					t_env;

typedef struct s_list
{
	char			**tokens;
	char			*argv;
	int				size;
	int				type;
	struct s_env	*env;
	t_redir			*redirections;
	struct s_list	*next;
}					t_list;

typedef struct s_word_split_params
{
	t_list	*node;
	int		*j;
	int		*count;
	t_env	*env;
	char	*orig;
	char	*exp;
}			t_word_split_params;

typedef struct s_special_case_ctx
{
	t_list	*node;
	int		*j;
	int		*count;
	char	**orig;
	char	**exp;
	int		len;
}			t_special_case_ctx;

typedef struct s_token_params
{
	t_list	*node;
	int		*j;
	int		*count;
	char	*orig;
}			t_token_params;

typedef struct s_heredoc_vars
{
	int		expand;
	t_env	*env;
}			t_heredoc_vars;

typedef struct s_token_manager
{
	char	***tokens;
	int		*count;
	int		*j;
}			t_token_manager;

typedef struct s_expansion_data
{
	char	*orig;
	char	*exp;
	int		had_assign;
	int		flag;
}			t_expansion_data;

typedef struct s_expansion_args
{
	char	***tokens;
	int		*count;
	int		*j;
	t_env	*env;
}			t_expansion_args;

int		ambigios(int should_update, int new_status);
int		exit_status(int should_update, int new_status);
void	sigint_handler(int sig);
int		check_unclosed_quotes(char *line);
int		ft_parser_quotes(char *line, int i, char quote);
char	*ft_process_quotes(char *s, char c);
void	copy_skip_quotes(char *src, int *idx, int len, char *dst);
int		count_letter(char *s, char c, int i);
int		ft_parser(t_list **list, char **line, t_env *env);
int		ft_size(char *line);
int		ft_type(char *line);
int		ft_strncmp(char *s1, char *s2, int n);
int		ft_line_error(char *line);
int		ft_check_bonus_syntax(char *line);
int		ft_check_redirections(char *line);
int		ft_check_pipes(char *line);
int		ft_three_pipe(char *line);
int		process_token_loop(t_list **list, char *temp, t_env *env_c);
int		process_new_token(t_list **lst, t_list *node, char *line, t_env *env);
int		init_token_node(t_list **list, t_list **new, char *line, t_env *env);
void	free_token(char **tokens);
void	ft_lstclear(t_list **lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_free_split(char **split);
char	**ft_malloc_error(char **arr);
void	ft_exite(t_list **list, t_list **new, char *line);
char	**ft_split(const char *s, char c);
char	**ft_split_minishell(char *s, char c);
int		count_word(char *s, char c);
char	*create_word(char *s, char c);
int		expanded_length(const char *str, int *flag, t_env *env);
char	*build_expanded(const char *str, t_env *env);
int		is_assignment_word(const char *s);
int		copy_and_tokenize(t_list **list, t_list *cmd, char *line, t_env *env);
void	copy_word_split_tokens(t_token_params *params, char **new_toks,
			char **parts, int pcount);
int		setup_word_split_arrays(t_token_params *params, char ***parts,
			char ***new_toks, int *pcount);
int		handle_expansion_split(char ***tokens, int *count, int j, char *exp);
char	**create_new_token_array(char **tokens, int count, int j, char **parts);
int		process_single_token(char ***tokens, int *count, int *j, t_env *env);
void	free_array(char **arr);
int		process_token_expan(t_token_manager *token_mgr,
			t_expansion_data *exp_data);
int		exit_quite(int update, int n_status);
void	her(int sig);
int		empty(int should_update, int new_status);
void	type_2(int type);
int		expand(int should_update, int new_status);
int		check_print(int should_update, int new_status);
int		check_quoted_assignment(t_expansion_data *exp_data);
int		handle_token_splitting(t_token_manager *token_mgr,
			t_expansion_data *exp_data, int j);
int		assign_expanded_token(t_token_manager *token_mgr,
			t_expansion_data *exp_data);
int		is_dollar_inside_double_quotes(const char *s);
int		max_heredoc(int should_update, int new_status);

#endif
