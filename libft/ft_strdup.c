/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 21:43:18 by mmaquine          #+#    #+#             */
/*   Updated: 2025/07/30 12:27:45 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
The function returns a pointer to a new string which is a duplicate of the
string s. Memory for the new string is obtained with malloc(3), and can be freed
with free(3). On success, the ft_strdup() function returns a pointer to the
duplicated string. It returns NULL if insufficient memory was available.
*/
char	*ft_strdup(const char *s)
{
	size_t	slen;
	char	*dup;

	slen = ft_strlen(s);
	dup = (char *)ft_calloc(slen + 1, sizeof(char));
	if (!dup)
		return (NULL);
	dup = (char *)ft_memcpy(dup, s, slen);
	return (dup);
}
