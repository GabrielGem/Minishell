/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 16:14:49 by gabrgarc          #+#    #+#             */
/*   Updated: 2025/12/21 09:38:05 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
*	hash(DJB2)
*/

unsigned int	hash_function(char *key, int size)
{
	unsigned long	hash;
	char			c;

	hash = 5381;
	while (*key)
	{
		c = *key;
		hash = ((hash << 5) + hash) + c;
		key++;
	}
	return (hash % size);
}
