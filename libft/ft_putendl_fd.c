/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:48:53 by mmaquine          #+#    #+#             */
/*   Updated: 2025/09/03 16:38:50 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Outputs the string 's' to the specified file descriptor 'fd' followed by a
newline
*/
int	ft_putendl_fd(char *s, int fd)
{
	int	printed;

	printed = 0;
	printed += ft_putstr_fd(s, fd);
	printed += ft_putchar_fd('\n', fd);
	return (printed);
}
