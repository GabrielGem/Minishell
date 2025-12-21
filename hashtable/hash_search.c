/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 17:30:45 by gabrgarc          #+#    #+#             */
/*   Updated: 2025/12/21 13:59:37 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

char	*hash_search(t_hash_table *table, char *key)
{
	unsigned int	index;
	t_hash_item		*actual_item;
	int				key_len;

	if (!table || !key)
		return (NULL);
	index = hash_function(key, table->size);
	actual_item = table->items[index];
	if (!actual_item)
		return (NULL);
	key_len = ft_strlen(key) + 1;
	while (actual_item)
	{
		if (ft_strncmp(actual_item->key, key, key_len) == 0)
			return (actual_item->value);
		actual_item = actual_item->next;
	}
	return (NULL);
}
