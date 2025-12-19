/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 10:02:00 by mmaquine          #+#    #+#             */
/*   Updated: 2025/10/24 16:15:29 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_puthex(size_t n, char to_upper)
{
	int	i;

	i = 0;
	if (n >= 16)
		i += ft_puthex(n / 16, to_upper);
	if (to_upper)
		i += ft_putchar_fd("0123456789ABCDEF"[n % 16], 1);
	else
		i += ft_putchar_fd("0123456789abcdef"[n % 16], 1);
	return (i);
}

static int	put_pointer(void *ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return (ft_putstr_fd("(nil)", 1));
	i += ft_putstr_fd("0x", 1);
	i += ft_puthex((size_t)ptr, 0);
	return (i);
}

static int	putstr(char *str)
{
	if (!str)
		return (ft_putstr_fd("(null)", 1));
	else
		return (ft_putstr_fd(str, 1));
}

static int	conversion(char *c, va_list arg)
{
	if (*c == 'c')
		return (ft_putchar_fd((char)va_arg(arg, int), 1));
	if (*c == 's')
		return (putstr(va_arg(arg, char *)));
	if (*c == 'p')
		return (put_pointer(va_arg(arg, void *)));
	if (*c == 'd' || *c == 'i')
		return (ft_putnbr_fd(va_arg(arg, int), 1));
	if (*c == 'l')
		return (ft_putnbr_fd(va_arg(arg, long), 1));
	if (*c == 'u')
		return (ft_putnbr_u((unsigned int)va_arg(arg, unsigned int), 1));
	if (*c == 'x')
		return (ft_puthex((unsigned int)va_arg(arg, int), 0));
	if (*c == 'X')
		return (ft_puthex((unsigned int)va_arg(arg, int), 1));
	if (*c == '%')
		return (ft_putchar_fd('%', 1));
	return (0);
}

/*
Upon succesful return, these functions return the number of bytes printed
excluding the null byte used to end output to strings)
 */
int	ft_printf(const	char *format, ...)
{
	va_list	ptr;
	int		total;

	total = 0;
	if (!format)
		return (-1);
	va_start(ptr, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			total += conversion((char *)format, ptr);
		}
		else
			total += ft_putchar_fd(*format, 1);
		format++;
	}
	va_end(ptr);
	return (total);
}
