/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_update_tag.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 16:29:12 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/22 15:52:48 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

int	hash_update_tag(t_hash_table *table, char *key, t_hash_type old_tag, \
t_hash_type new_tag)
{
	t_hash_item	*item;
	int			index;
	int			key_len;

	if (!table || !key)
		return (-1);
	index = hash_function(key, table->size);
	item = table->items[index];
	key_len = ft_strlen(key) + 1;
	while (item)
	{
		if (ft_strncmp(item->key, key, key_len) == 0
			&& item->tag == old_tag)
		{
			item->tag = new_tag;
			return (0);
		}
		item = item->next;
	}
	return (-1);
}
