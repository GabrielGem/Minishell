/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:15:14 by mmaquine          #+#    #+#             */
/*   Updated: 2026/02/13 12:57:39 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Similar to ft_strcmp, except it compares only the first (at most) n bytes of s1
and s2.
*/
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

/*
Returns an integer indicating the result of the comparison, as follows:
- 0, if the s1 and s2 are equal
- a negative value if s1 is less than s2;
- a positive value if s1 is greater tha s2.
*/
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			n;
	size_t			ns2;

	if (s1 == NULL && s2 == NULL)
		return (0);
	if (s2 == NULL)
		return (s1[0]);
	if (s1 == NULL)
		return (-s2[0]);
	n = ft_strlen(s1);
	ns2 = ft_strlen(s2);
	if (ns2 > n)
		n = ns2;
	return (ft_strncmp(s1, s2, n));
}
