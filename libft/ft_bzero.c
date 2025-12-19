/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:07:56 by mmaquine          #+#    #+#             */
/*   Updated: 2025/07/16 15:22:35 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
The function erases the data in the n bytes of the memory starting at the
location pointed to by s, by writing zeros (bytes containing '\0') to that area
*/
void	*ft_bzero(void *s, size_t n)
{
	return (ft_memset(s, '\0', n));
}
