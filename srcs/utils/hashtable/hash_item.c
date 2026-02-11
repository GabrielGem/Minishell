/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_item.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:33:21 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/11 18:10:27 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

t_hash_item	*hash_item(char *key, char *value, t_hash_type tag)
{
	t_hash_item	*item;

	if (!key || tag < ENV || tag > EXPORT)
		return (NULL);
	item = ft_calloc(sizeof(t_hash_item), 1);
	if (!item)
		return (NULL);
	item->tag = tag;
	item->key = ft_strdup(key);
	if (!item->key)
	{
		free(item);
		return (NULL);
	}
	if (value)
	{
		item->value = ft_strdup(value);
		if (!item->value)
		{
			free(item->key);
			free(item);
			return (NULL);
		}
	}
	return (item);
}
