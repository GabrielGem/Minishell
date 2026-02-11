/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_for_array_of_items.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 16:29:26 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/11 18:11:39 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_hash_item	**table_for_array_of_items(t_hash_table *table, int count, \
			t_hash_type tag)
{
	t_hash_item	**array;
	t_hash_item	*item;
	int			i;
	int			j;

	array = ft_calloc(count + 1, sizeof(t_hash_item *));
	if (!array)
		return (NULL);
	i = 0;
	j = 0;
	while (i < table->size)
	{
		item = table->items[i];
		while (item)
		{
			if (item->tag == tag)
			{
				array[j] = item;
				j++;
			}
			item = item->next;
		}
		i++;
	}
	return (array);
}
