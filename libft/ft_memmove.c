/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:45:16 by mmaquine          #+#    #+#             */
/*   Updated: 2025/07/31 12:04:59 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_cpy_fw(unsigned char *dt, const unsigned char *sc, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		dt[i] = sc[i];
		i++;
	}
}

static void	ft_cpy_bw(unsigned char *dt, const unsigned char *sc, size_t size)
{
	size--;
	while (size > 0)
	{
		*(dt + size) = *(sc + size);
		size--;
	}
	*dt = *sc;
}

/*
The function copies n bytes from memory area src to memory area dest. The memory
areas may overlap: copying takes place as though the bytes in src are first
copied into a temporary array that does not overlap src or dst, and the bytes
are then copied fron the temporary array to dest;
*/
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const unsigned char	*tsrc;
	unsigned char		*tdest;

	if (dest == NULL && src == NULL)
		return (dest);
	tsrc = src;
	tdest = dest;
	if (src - dest < (long)n && src - dest >= 0)
	{
		ft_cpy_fw(tdest, tsrc, n);
		return (dest);
	}
	else if (dest - src < (long)n && dest - src >= 0)
	{
		ft_cpy_bw(tdest, tsrc, n);
		return (dest);
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
