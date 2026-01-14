/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:25:01 by mmaquine          #+#    #+#             */
/*   Updated: 2025/07/30 13:23:15 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_str(const char *s, char c)
{
	size_t	count;
	size_t	pos;

	if (s == NULL)
		return (0);
	pos = 0;
	count = 0;
	while (s[pos])
	{
		if (pos == 0 && (s[pos] != c))
			count++;
		if (pos != 0 && (s[pos - 1] == c && s[pos] != c))
			count++;
		pos++;
	}
	return (count);
}

static char	*get_string(const char *s, char c, size_t *next)
{
	size_t	start;
	size_t	end;
	char	*string;

	while (s[*next] && (s[*next] == c))
		(*next)++;
	start = (*next);
	while (s[*next] && (s[*next] != c))
		(*next)++;
	end = (*next);
	string = (char *)ft_calloc(end - start + 1, sizeof(char));
	if (!string)
		return (NULL);
	string = ft_memcpy(string, &s[start], end - start);
	return (string);
}

char	**ft_split(const char *s, char c)
{
	char	**split;
	size_t	pos;
	size_t	next_str_pos;

	if (s == NULL)
		return (NULL);
	split = (char **)ft_calloc((count_str(s, c) + 1), sizeof(char *));
	if (!split)
		return (NULL);
	pos = 0;
	next_str_pos = 0;
	while (pos < count_str(s, c))
	{
		split[pos] = get_string(s, c, &next_str_pos);
		if (!split[pos])
		{
			while (pos > 0)
				free(split[--pos]);
			free(split);
			return (NULL);
		}
		pos++;
	}
	return (split);
}
