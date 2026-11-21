/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 14:56:39 by akella            #+#    #+#             */
/*   Updated: 2025/06/24 17:18:44 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expande.h"

int	handle_dollar(const char *str, int *pos, int *expanded, t_env *env)
{
	if (str[*pos + 1] == '?')
		return (handle_exit_status(pos, expanded));
	return (handle_var_name(str, pos, expanded, env));
}

int	handle_exit_status(int *pos, int *expanded)
{
	char	*ret_str;
	int		len;

	ret_str = ft_itoa(exit_status(0, 0));
	if (!ret_str)
		return (-1);
	len = ft_strlen(ret_str);
	free(ret_str);
	*expanded = 1;
	*pos += 2;
	return (len);
}

int	handle_var_name(const char *str,
		int *pos, int *expanded, t_env *env)
{
	int		start;
	int		end;
	char	*var_name;
	char	*value;
	int		len;

	start = *pos + 1;
	if (!is_valid_var_start_char(str[start]))
		return ((*pos)++, 1);
	end = start;
	while (is_valid_var_char(str[end]))
		end++;
	var_name = ft_substr(str, start, end - start);
	if (!var_name)
		return (-1);
	value = get_env_value(var_name, env);
	free(var_name);
	len = 0;
	if (value)
		len = ft_strlen(value);
	*expanded = 1;
	*pos = end;
	return (len);
}

int	is_valid_var_start_char(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_');
}

int	is_valid_var_char(char c)
{
	return (is_valid_var_start_char(c) || (c >= '0' && c <= '9'));
}
