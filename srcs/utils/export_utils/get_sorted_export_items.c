/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sorted_export_items.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 14:53:05 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/22 17:08:53 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_hash_item	**get_sorted_export_items(t_hash_table *table)
{
	t_hash_item	**env_items;
	t_hash_item	**export_items;
	t_hash_item	**result;
	int			env_count;
	int			export_count;

	env_count = count_items_by_tag(table, ENV);
	env_items = table_for_array_of_items(table, env_count, ENV);
	export_count = count_items_by_tag(table, EXPORT);
	export_items = table_for_array_of_items(table, export_count, EXPORT);
	result = (t_hash_item **)ft_join_array_of_pointers((void **)env_items, \
	(void **)export_items);
	free(env_items);
	free(export_items);
	sort_array_of_items(result, env_count + export_count);
	return (result);
}
