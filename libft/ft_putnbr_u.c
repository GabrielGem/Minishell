/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:04:17 by mmaquine          #+#    #+#             */
/*   Updated: 2025/09/03 17:14:39 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_u(unsigned int n, int fd)
{
	int	i;

	i = 0;
	if (n >= 10)
		i += ft_putnbr_fd(n / 10, fd);
	i += ft_putchar_fd(n % 10 + '0', fd);
	return (i);
}
