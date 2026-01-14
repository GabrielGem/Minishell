/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:04:35 by mmaquine          #+#    #+#             */
/*   Updated: 2025/07/29 13:15:13 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
The function compares the first n bytes (each interpreted as unsigned char) of
the memory areas s1 and s2. The return is an integer less than, equal to or,
grater than zero if the first n bytes of s1 is found, respectively, to be less
than, to match, or be greater than first n bytes of s2.
*/
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ts1;
	const unsigned char	*ts2;
	size_t				i;

	ts1 = s1;
	ts2 = s2;
	i = 0;
	while (i < n && (ts1[i] == ts2[i]))
		i++;
	if (i == n)
		return (0);
	else
		return (ts1[i] - ts2[i]);
}
