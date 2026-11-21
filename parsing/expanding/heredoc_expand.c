/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 21:21:13 by akella            #+#    #+#             */
/*   Updated: 2025/07/04 14:15:21 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expande.h"

void	handle_expansion_cases_herdoc(t_expansion_ctx *ctx)
{
	handle_quotes_vars_and_default(ctx);
}

int	expanded_length_heredoc(const char *str, int *flag, t_env *env)
{
	t_expansion_ctx	ctx;

	ctx.str = str;
	ctx.i = 0;
	ctx.len = 0;
	ctx.flag = flag;
	ctx.env = env;
	while (ctx.str[ctx.i])
		handle_expansion_cases_herdoc(&ctx);
	return (ctx.len);
}

static void	process_expansion_chars_heredoc(char **src, char **dst, int *j,
	t_env *env)
{
	process_expansion_chars_extra(src, dst, j, env);
}

char	*build_expanded_heredoc(const char *str, t_env *env)
{
	int		j;
	int		flag;
	int		len;
	char	*dst;
	char	*src;

	j = 0;
	flag = 0;
	len = expanded_length(str, &flag, env);
	if (len == -1)
		return (NULL);
	dst = ft_malloc(len + 1);
	src = (char *)str;
	while (*src)
		process_expansion_chars_heredoc(&src, &dst, &j, env);
	dst[j] = '\0';
	return (dst);
}
