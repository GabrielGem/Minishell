/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:15:14 by mmaquine          #+#    #+#             */
/*   Updated: 2025/11/10 10:40:07 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*ss1;
	unsigned char	*ss2;

	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	while ((*ss1 == *ss2) && (n > 0) && *ss1)
	{
		ss1++;
		ss2++;
		n--;
	}
	if (n == 0)
		return (0);
	return (*ss1 - *ss2);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			n;
	size_t			ns2;

	n = ft_strlen(s1);
	ns2 = ft_strlen(s2);
	if (ns2 > n)
		n = ns2;
	return (ft_strncmp(s1, s2, n));
}
