/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 20:36:05 by akella            #+#    #+#             */
/*   Updated: 2025/06/29 15:17:43 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**ft_malloc_error(char **arr)
{
	unsigned int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (NULL);
}

char	*ft_process_quotes(char *s, char delim)
{
	while (*s != delim && *s != '\0')
	{
		if (*s == 34)
		{
			s++;
			while (*s && *s != 34)
				s++;
		}
		else if (*s == 39)
		{
			s++;
			while (*s && *s != 39)
				s++;
		}
		if (*s)
			s++;
	}
	return (s);
}

int	count_word(char *s, char c)
{
	int	word;

	word = 0;
	while (*s)
	{
		if (*s != ' ' && *s != '\t')
		{
			word++;
			s = ft_process_quotes(s, c);
		}
		else
			s++;
	}
	return (word);
}

int	count_letter(char *s, char c, int i)
{
	i++;
	while (s[i] && s[i] != c)
	{
		if (s[i] == 34)
		{
			i++;
			while (s[i] && s[i] != 34)
				i++;
		}
		else if (s[i] == 39)
		{
			i++;
			while (s[i] && s[i] != 39)
				i++;
		}
		if (s[i])
			i++;
	}
	return (i);
}
