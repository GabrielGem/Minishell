/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:12:04 by mmaquine          #+#    #+#             */
/*   Updated: 2026/02/19 14:21:00 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_islower(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c);
	else
		return (0);
}

static	int	ft_isupper(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c);
	else
		return (0);
}

/*
Return 1 if c is [a-zA-Z]
*/
int	ft_isalpha(int c)
{
	return (ft_islower(c) || ft_isupper(c));
}
