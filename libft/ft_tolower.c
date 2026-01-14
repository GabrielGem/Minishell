/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:08:11 by mmaquine          #+#    #+#             */
/*   Updated: 2025/09/29 15:46:30 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Convert letters to lowercase.
Return c if the conversion was not possible.
*/
int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c ^ 0x20);
	else
		return (c);
}
