/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akella <akella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 20:27:08 by akella            #+#    #+#             */
/*   Updated: 2025/07/06 16:04:00 by akella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	copy_quoted_content(char *s, char *arr, int *j, int *k)
{
	if (s[*j] == 34)
	{
		(*j)++;
		arr[(*k)++] = s[(*j) - 1];
		while (s[*j] && s[*j] != 34)
			arr[(*k)++] = s[(*j)++];
	}
	else if (s[*j] == 39)
	{
		(*j)++;
		arr[(*k)++] = s[(*j) - 1];
		while (s[*j] && s[*j] != 39)
			arr[(*k)++] = s[(*j)++];
	}
	if (s[*j])
		arr[(*k)++] = s[(*j)++];
}

char	*create_word(char *s, char c)
{
	int		i;
	char	*arr;
	int		j;
	int		k;

	i = count_letter(s, c, -1);
	arr = (char *)ft_malloc((i + 1) * sizeof(char));
	if (!arr)
		return (NULL);
	j = 0;
	k = 0;
	while (s[j] && s[j] != c && k < i)
	{
		arr[k] = s[j];
		if (s[j] == 34 || s[j] == 39)
			copy_quoted_content(s, arr, &j, &k);
		else
		{
			arr[k++] = s[j++];
		}
	}
	arr[k] = '\0';
	return (arr);
}

char	**ft_split_whitespace(char *s)
{
	char	*temp;
	char	**result;
	int		i;

	if (!s)
		return (NULL);
	temp = ft_strdup(s);
	if (!temp)
		return (NULL);
	i = 0;
	while (temp[i])
	{
		if (temp[i] == '\t' || temp[i] == '\n')
			temp[i] = ' ';
		i++;
	}
	result = ft_split_minishell(temp, ' ');
	free(temp);
	return (result);
}
