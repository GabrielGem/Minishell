/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 16:14:33 by gabrgarc          #+#    #+#             */
/*   Updated: 2025/12/21 09:52:38 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

t_hash_table	*create_table(int size)
{
	t_hash_table	*table;

	table = ft_calloc(sizeof(t_hash_table), 1);
	if (!table)
		return (NULL);
	table->items = ft_calloc(sizeof(t_hash_item *), size);
	if (!table->items)
	{
		free(table);
		return (NULL);
	}
	table->size = size;
	table->count = 0;
	return (table);
}
