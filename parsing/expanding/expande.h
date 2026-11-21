/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expande.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:45:49 by akella            #+#    #+#             */
/*   Updated: 2025/07/10 17:47:02 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDE_H
# define EXPANDE_H

# include "../../minishell.h"

typedef struct s_expansion_ctx
{
	const char	*str;
	int			i;
	int			len;
	int			*flag;
	t_env		*env;
}				t_expansion_ctx;

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
void	handle_expansion_cases_herdoc(t_expansion_ctx *ctx);
int		handle_quotes_vars_and_default(t_expansion_ctx *ctx);

#endif