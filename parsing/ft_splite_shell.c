/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splite_shell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaissi <zaissi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:17:46 by akella            #+#    #+#             */
/*   Updated: 2025/07/05 16:31:44 by zaissi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**ft_fill_arr(char *s, char c, char	**arr, int word)
{
	int	i;

	i = 0;
	while (i < word && *s != '\0')
	{
		if (*s != c)
		{
			arr[i] = create_word(s, c);
			if (arr[i] == NULL)
				return (ft_malloc_error(arr));
			s = ft_process_quotes(s, c);
			i++;
		}
		s++;
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_split_minishell(char *s, char c)
{
	char	**arr;
	int		word;

	if (s == NULL)
		return (NULL);
	word = count_word(s, c);
	arr = (char **)ft_malloc((word + 1) * sizeof(char *));
	if (arr == NULL)
		return (NULL);
	return (ft_fill_arr(s, c, arr, word));
}
