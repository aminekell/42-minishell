/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:37:44 by akella            #+#    #+#             */
/*   Updated: 2025/07/15 17:01:42 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

int	ft_atoi(const char *str)
{
	int			s;
	long long	r;
	long long	r2;

	s = 1;
	r = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			s = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		r2 = r;
		r = r * 10 + (*str - '0');
		if ((r / 10 != r2) && s == 1)
			return (-1);
		if ((r / 10 != r2) && s == -1)
			return (0);
		str++;
	}
	return ((int)(r * s));
}

void	error_exit(char *str)
{
	write(2, "minishell: exit: ", 17);
	write(2, str, ft_strlen(str));
	write(2, ": numeric argument required\n", 28);
	exit(255);
}

static int64_t	return_neg_value(uint64_t res)
{
	if (res == (uint64_t)LLONG_MAX + 1)
		return (LLONG_MIN);
	return (-(int64_t)res);
}

uint64_t	check_and_restore(uint64_t res, int sign, char c, char *str)
{
	if ((res > (uint64_t)LLONG_MAX / 10) || !ft_isdigit(c))
		error_exit(str);
	res = res * 10 + (c - '0');
	if (((sign == 1 && res > (uint64_t)LLONG_MAX)
			|| (sign == -1 && res - 1 > (uint64_t)LLONG_MAX)) && res != 0)
		error_exit(str);
	return (res);
}

int64_t	exit_atoi(char *str)
{
	int			sign;
	uint64_t	res;
	int			i;

	(1) && (sign = 1, res = 0, i = 0);
	while (ft_isspace(str[i]))
		i++;
	if ((str[i] == '-' || str[i] == '+') && ft_isdigit(str[i + 1]))
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		res = check_and_restore(res, sign, str[i], str);
		i++;
	}
	while (ft_isspace(str[i]))
		i++;
	if (str[i] != '\0')
		error_exit(str);
	if (sign == -1)
		return (return_neg_value(res));
	return ((int64_t)res);
}
