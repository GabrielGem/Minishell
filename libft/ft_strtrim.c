/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:58:40 by mmaquine          #+#    #+#             */
/*   Updated: 2025/07/30 12:26:05 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	in_set(char c, const char *set)
{
	size_t	i;

	i = 0;
	if (set == NULL)
		return (0);
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

/*
Allocates memory and returns a copy of 's1' with characters from set removed
from the beginning and the end.
Return a trimmed string. NULL if the allocation fails.
*/
char	*ft_strtrim(const char *s1, const char *set)
{
	char	*trimmed;
	size_t	pos;
	size_t	pos_end;

	pos = 0;
	if (s1 == NULL)
		return (NULL);
	while (s1[pos] && in_set(s1[pos], set))
		pos++;
	pos_end = ft_strlen(s1);
	pos_end--;
	while (pos_end > 0 && in_set(s1[pos_end], set))
		pos_end--;
	if (pos_end >= pos)
	{
		trimmed = ft_substr(s1, pos, pos_end - pos + 1);
		return (trimmed);
	}
	else
		return (ft_strdup((char *)""));
}
/*
#include <stdio.h>
#include <bsd/string.h>
int	main()
{
	char *s1 = "abcdba";
	char *set = "acb";
	char *ret = ft_strtrim(s1, set);

	printf("%s\n", ret);
}*/