/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_items_by_tag.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:01:56 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/01/29 15:02:17 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

int	count_items_by_tag(t_hash_table *table, t_hash_type tag)
{
	t_hash_item	*item;
	int			count;
	int			i;

	i = 0;
	count = 0;
	while (i < table->size)
	{
		item = table->items[i];
		while (item)
		{
			if (item->tag == tag)
				count++;
			item = item->next;
		}
		i++;
	}
	return (count);
}
