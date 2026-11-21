/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanded_length.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 18:26:33 by akella            #+#    #+#             */
/*   Updated: 2025/07/14 22:38:36 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expande.h"

int	handle_quotes_vars_and_default(t_expansion_ctx *ctx)
{
	int	ret;

	if (ctx->str[ctx->i] == '"')
	{
		ret = handle_double_quote(ctx->str, &(ctx->i), ctx->flag, ctx->env);
		if (ret == -1)
			return (-1);
		ctx->len += ret;
	}
	else if (ctx->str[ctx->i] == '$')
	{
		ret = ft_len_var(ctx->str, &(ctx->i), ctx->flag, ctx->env);
		if (ret == -1)
			return (-1);
		ctx->len += ret;
	}
	else
	{
		ctx->len++;
		ctx->i++;
	}
	return (0);
}

static int	handle_expansion_cases(t_expansion_ctx *ctx)
{
	if (ctx->str[ctx->i] == '\'')
		ctx->len = handle_single_quote(ctx->str, &(ctx->i), ctx->len);
	else
		handle_quotes_vars_and_default(ctx);
	return (0);
}

int	expanded_length(const char *str, int *flag, t_env *env)
{
	t_expansion_ctx	ctx;
	int				status;

	ctx.str = str;
	ctx.i = 0;
	ctx.len = 0;
	ctx.flag = flag;
	ctx.env = env;
	while (ctx.str[ctx.i])
	{
		status = handle_expansion_cases(&ctx);
		if (status == -1)
			return (-1);
	}
	return (ctx.len);
}

static int	process_double_quote_content(const char *str, int *pos,
			int *expanded, t_env *env)
{
	int	len;
	int	var_len;

	len = 0;
	len++;
	while (str[*pos] && str[*pos] != '"')
	{
		if (str[*pos] == '$')
		{
			var_len = handle_dollar(str, pos, expanded, env);
			if (var_len == -1)
				return (-1);
			len += var_len;
		}
		else
		{
			if (str[*pos] == '*')
				len += 2;
			else
				len += 1;
			(*pos)++;
		}
	}
	len++;
	return (len);
}

int	handle_double_quote(const char *str, int *idx, int *expanded, t_env *env)
{
	int	pos;
	int	len;

	len = 0;
	pos = *idx + 1;
	len = process_double_quote_content(str, &pos, expanded, env);
	if (len == -1)
		return (-1);
	if (str[pos] == '"')
		pos++;
	*idx = pos;
	return (len);
}
