/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:45:31 by mmaquine          #+#    #+#             */
/*   Updated: 2025/07/16 19:46:23 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
Copy the input string into a destination string. If the destination buffer isn't
large enough to hold teh copy, the resulting string is truncated (but it is
guarasnteed to be null-terminated). It returns the length of the string, or -1
if it truncated.
*/
size_t	ft_strlcat(char *dst, const char *src, size_t dsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < dsize && dst[i])
	{
		i++;
	}
	while ((i + j + 1) < dsize && src[j])
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i != dsize)
	{
		dst[i + j] = '\0';
	}
	return (i + ft_strlen(src));
}
