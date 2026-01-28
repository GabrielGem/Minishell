/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_delete.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:32:04 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/01/28 18:08:23 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

static void	remove_item(t_hash_table *table, t_hash_item *actual,
				t_hash_item *prev, unsigned int index);

int	hash_delete(t_hash_table *table, char *key, t_hash_type tag)
{
	unsigned int	index;
	t_hash_item		*actual_item;
	t_hash_item		*prev_item;
	int				key_len;

	if (!table || !key || tag < ENV || tag > EXPORT)
		return (-1);
	index = hash_function(key, table->size);
	actual_item = table->items[index];
	prev_item = NULL;
	key_len = ft_strlen(key) + 1;
	while (actual_item != NULL)
	{
		if (ft_strncmp(actual_item->key, key, key_len) == 0
			&& actual_item->tag == tag)
		{
			remove_item(table, actual_item, prev_item, index);
			return (0);
		}
		prev_item = actual_item;
		actual_item = actual_item->next;
	}
	return (1);
}

static void	remove_item(t_hash_table *table, t_hash_item *actual_item,
		t_hash_item *prev_item, unsigned int index)
{
	if (prev_item == NULL)
		table->items[index] = actual_item->next;
	else
		prev_item->next = actual_item->next;
	destroy_item(actual_item);
}
