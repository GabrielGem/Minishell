/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_destroy_item.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 09:45:53 by gabrgarc          #+#    #+#             */
/*   Updated: 2025/12/21 14:36:23 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

void	destroy_item(t_hash_item *item)
{
	if (!item)
		return ;
	free(item->key);
	free(item->value);
	free(item);
}
