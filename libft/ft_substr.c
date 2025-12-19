/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:55:12 by mmaquine          #+#    #+#             */
/*   Updated: 2025/09/29 10:06:25 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Allocates memory (using malloc(3)) and returns a substring from the string 's'
The substring starts at index 'start' and has a maximum length of 'len'.
*/
char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	charleft;
	size_t	st;
	char	*sub;

	if (!s || !len)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_calloc(1, sizeof(char)));
	charleft = ft_strlen(&s[start]);
	if (charleft > len)
		charleft = len;
	sub = ft_calloc(charleft + 1, sizeof(char));
	if (!sub)
		return (NULL);
	st = 0;
	while (s[start] && (st < len))
	{
		sub[st] = s[start];
		st++;
		start++;
	}
	return (sub);
}
