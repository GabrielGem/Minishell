/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 10:06:38 by mmaquine          #+#    #+#             */
/*   Updated: 2025/09/29 10:08:26 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	char	*str1;
	char	*str2;
	char	*start;

	str1 = (char *)s1;
	str2 = (char *)s2;
	joined = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, 1);
	if (!joined)
		return (NULL);
	start = joined;
	while (*str1)
		*joined++ = *str1++;
	while (*str2)
		*joined++ = *str2++;
	return (start);
}
