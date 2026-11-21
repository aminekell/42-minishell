/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_d_s_q.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:55:39 by akella            #+#    #+#             */
/*   Updated: 2025/07/12 23:25:04 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expande.h"

void	copy_literal_single(int *dst_idx, char **src, char **dst)
{
	int	i;

	i = *dst_idx;
	(*src)++;
	while (**src && **src != '\'')
		(*dst)[i++] = *(*src)++;
	if (**src == '\'')
		(*src)++;
	*dst_idx = i;
}

void	insert_exit_status(char **dst, char *status, int *dst_idx, char **src)
{
	int	i;
	int	j;

	i = 0;
	j = *dst_idx;
	while (status[i])
		(*dst)[j++] = status[i++];
	*dst_idx = j;
	*src += 2;
}

static int	ft_len_special(const char *s, int *i, int *flag)
{
	char	*ret_str;
	int		len;

	if (s[*i + 1] == '?')
	{
		*flag = 1;
		*i += 2;
		ret_str = ft_itoa(exit_status(0, 0));
		if (!ret_str)
			return (-1);
		len = ft_strlen(ret_str);
		free(ret_str);
		return (len);
	}
	if (s[*i + 1] == '\0'
		|| !((s[*i + 1] >= 'A' && s[*i + 1] <= 'Z')
			|| (s[*i + 1] >= 'a' && s[*i + 1] <= 'z')
			|| (s[*i + 1] >= '0' && s[*i + 1] <= '9')
			|| s[*i + 1] == '_'))
	{
		(*i)++;
		return (1);
	}
	return (0);
}

static char	*extract_var_name(const char *s, int *end)
{
	int	start;

	start = *end + 1;
	*end = start;
	while ((s[*end] >= 'A' && s[*end] <= 'Z')
		|| (s[*end] >= 'a' && s[*end] <= 'z')
		|| (s[*end] >= '0' && s[*end] <= '9')
		|| s[*end] == '_')
		(*end)++;
	return (ft_substr(s, start, *end - start));
}

int	ft_len_var(const char *s, int *i, int *flag, t_env *env)
{
	char	*var_name;
	char	*value;
	int		special_len;
	int		var_name_len;

	special_len = ft_len_special(s, i, flag);
	if (special_len)
		return (special_len);
	var_name = extract_var_name(s, i);
	if (!var_name)
		return (-1);
	value = get_env_value(var_name, env);
	var_name_len = ft_strlen(var_name);
	free(var_name);
	*flag = 1;
	if (value)
		return (ft_strlen(value));
	return (1 + var_name_len);
}
