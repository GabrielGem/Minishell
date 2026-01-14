/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 09:51:59 by mmaquine          #+#    #+#             */
/*   Updated: 2025/09/03 16:37:08 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
Outputs a character 'c' to the specified file descriptor 'fd'
*/
int	ft_putchar_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}
