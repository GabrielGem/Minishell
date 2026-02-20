/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:22:19 by mmaquine          #+#    #+#             */
/*   Updated: 2026/02/19 14:23:03 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Return 1 if c is a digit or alpha. See ft_isdigit and ft_isalpha.
*/
int	ft_isalnum(int c)
{
	return (ft_isdigit(c) || ft_isalpha(c));
}
