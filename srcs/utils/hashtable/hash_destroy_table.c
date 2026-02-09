/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_destroy_table.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 19:27:21 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/06 11:03:16 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

void	destroy_table(t_hash_table *table)
{
	t_hash_item	*item;
	t_hash_item	*next;
	int			index;

	if (!table || !table->items)
		return ;
	index = 0;
	while (index < table->size)
	{
		item = table->items[index];
		while (item)
		{
			next = item->next;
			destroy_item(item);
			item = next;
		}
		index++;
	}
	free(table->items);
	free(table);
}
