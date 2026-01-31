/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_upsert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:35:42 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/01/31 14:15:31 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

static int	update_if_exists(t_hash_item *item, char *key, char *value, t_hash_type tag);

int	hash_upsert(t_hash_table *table, char *key, char *value, t_hash_type tag)
{
	t_hash_item		*new_item;
	unsigned int	index;
	int				update_result;

	if (!table || !key || tag < ENV || tag > SET)
		return (-1);
	index = hash_function(key, table->size);
	if (table->items[index] != NULL)
	{
		update_result = update_if_exists(table->items[index], key, value, tag);
		if (update_result == -1)
			return (-1);
		if (update_result == 1)
			return (0);
	}
	new_item = hash_item(key, value, tag);
	if (!new_item)
		return (-1);
	new_item->next = table->items[index];
	table->items[index] = new_item;
	table->count += 1;
	return (0);
}

static int	update_if_exists(t_hash_item *item, char *key, char *value, t_hash_type tag)
{
	t_hash_item	*actual_item;
	char		*new_value;
	int			key_len;

	key_len = ft_strlen(key) + 1;
	actual_item = item;
	while (actual_item != NULL)
	{
		if (ft_strncmp(actual_item->key, key, key_len) == 0)
		{
			new_value = ft_strdup(value);
			if (!new_value)
				return (-1);
			free(actual_item->value);
			actual_item->value = new_value;
			actual_item->tag = tag;
			return (1);
		}
		actual_item = actual_item->next;
	}
	return (0);
}
