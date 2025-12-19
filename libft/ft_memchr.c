/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:24:27 by mmaquine          #+#    #+#             */
/*   Updated: 2025/07/25 14:41:41 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*us;
	unsigned char	uc;

	i = 0;
	us = (void *)s;
	uc = (unsigned char)c;
	while (n > 0)
	{
		if (us[i] == uc)
			return ((void *)&us[i]);
		n--;
		i++;
	}
	return (NULL);
}
