/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checks.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:48:28 by akella            #+#    #+#             */
/*   Updated: 2025/07/03 16:36:05 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_CHECKS_H
# define SYNTAX_CHECKS_H

# include "../../minishell.h"

typedef struct s_quote_helper
{
	const char	*raw;
	char		*result;
	int			src;
	int			dst;
	int			len;
}	t_quote_helper;

typedef struct s_quote_helper_hc
{
	const char	*raw;
	char		*result;
	int			src;
	int			dst;
	int			len;
}	t_quote_helper_hc;

int		ft_syntax_error(void);
int		ft_line_error(char *line);
int		check_pipe_amp(char *line, int i);
int		ft_semicolon_and_pipe(char *line, int i);
int		check_pipe_start_end(char *line, int i);
int		ft_check_pipes(char *line);
int		validate_redir(char *line, int *i);
int		ft_check_redirections(char *line);
int		quote_loop(char *line);
int		check_unclosed_quotes(char *line);
int		check_parentheses(char *line);
int		skip_whitespace(char *line, int start, int len);
int		check_pipe_syntax(char *line, int i, int len);
int		check_ampersand_syntax(char *line, int i, int len);
void	process_quoted_segment(t_quote_helper *h, char quote);
char	*process_quotes_helper(t_quote_helper *h);
int		process_quoted_filename(char *line, int i, char q);
int		filename_end(const char *s, int i);
char	*handle_expanded_filename(char *expanded, int *idx, int end);
char	*process_quotes_filename(char *raw, int *idx, int end);

#endif