/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:33:36 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/18 17:04:13 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

char	*hash_search(t_hash_table *table, char *key, t_hash_type tag)
{
	unsigned int	index;
	t_hash_item		*actual_item;
	int				key_len;

	if (!table || !key || tag < ENV || tag > SET)
		return (NULL);
	index = hash_function(key, table->size);
	actual_item = table->items[index];
	if (!actual_item)
		return (NULL);
	key_len = ft_strlen(key) + 1;
	while (actual_item)
	{
		if (ft_strncmp(actual_item->key, key, key_len) == 0
			&& actual_item->tag == tag)
			return (actual_item->value);
		actual_item = actual_item->next;
	}
	return (NULL);
}
