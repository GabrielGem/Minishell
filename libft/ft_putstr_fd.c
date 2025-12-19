/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:55:35 by mmaquine          #+#    #+#             */
/*   Updated: 2025/09/03 16:44:51 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Outputs the string 's' to the specified file descriptor 'fd'
*/
int	ft_putstr_fd(char *s, int fd)
{
	int	printed;

	printed = 0;
	while (*s)
	{
		printed += ft_putchar_fd(*s, fd);
		s++;
	}
	return (printed);
}
