/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 14:00:37 by mmaquine          #+#    #+#             */
/*   Updated: 2026/01/15 14:12:18 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Checks for white-space characters. In the "C" and "POSIX" locales, these
	are: space, form-feed('\f'), newline ('\n'), carriage return ('\r'), hori-
	zontal tab ('\t'), and vertical tab ('\v')
*/
int	ft_isspace(int c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}
