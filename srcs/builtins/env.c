/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 14:12:36 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/14 17:45:01 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_env(t_data *context, char **args)
{
	t_hash_item		*item;
	t_hash_table	*table;
	int				i;

	(void)args;
	table = context->env;
	i = 0;
	while (i < table->size)
	{
		item = table->items[i];
		while (item)
		{
			if (item->tag == ENV)
				printf("%s=\"%s\"\n", item->key, item->value);
			item = item->next;
		}
		i++;
	}
	return (0);
}
