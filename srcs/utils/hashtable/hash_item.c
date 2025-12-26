/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_item.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 16:52:08 by gabrgarc          #+#    #+#             */
/*   Updated: 2025/12/23 17:29:08 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_hash_item	*hash_item(char *key, char *value)
{
	t_hash_item	*item;

	if (!key)
		return (NULL);
	item = ft_calloc(sizeof(t_hash_item), 1);
	if (!item)
		return (NULL);
	item->next = NULL;
	item->key = ft_strdup(key);
	item->value = ft_strdup(value);
	if (!item->key || !item->value)
	{
		free(item->key);
		free(item->value);
		free(item);
		return (NULL);
	}
	return (item);
}
