/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 14:12:36 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/09 18:36:51 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_env(t_data *context, char **args)
{
	t_hash_item	*item;
	int			i;

	(void)args;
	i = 0;
	while (i < table->size)
	{
		item = table->items[i];
		while (item)
		{
			if (items[i]->tag == ENV)
				printf("%s=\"%s\"\n", items[i]->key, items[i]->value);
			item = item->next;
		}
		i++;
	}
	return (0);
}
