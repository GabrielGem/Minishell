/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 19:31:58 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/16 11:04:55 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_numbers(unsigned long int n, int base)
{
	int	len;

	len = 0;
	while (n > 0)
	{
		n /= base;
		len++;
	}
	return (len);
}

char	*ft_uitoa_base(unsigned long int n, char *symbols)
{
	unsigned long int	num;
	int					len;
	int					base;
	char				*result;

	num = n;
	base = ft_strlen(symbols);
	len = count_numbers(n, base);
	result = ft_calloc(len + 1, sizeof(char));
	if (!result)
		return (NULL);
	while (len--)
	{
		result[len] = symbols[num % base];
		num /= base;
	}
	return (result);
}
