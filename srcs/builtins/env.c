/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 14:12:36 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/24 13:11:17 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_env(t_data *context, char **args)
{
	t_hash_item		*item;
	t_hash_table	*table;
	int				i;

	if (args[1])
	{
		ft_putstr_fd("minishell: env: too many arguments\n", 2);
		return (127);
	}
	table = context->env;
	i = 0;
	while (i < table->size)
	{
		item = table->items[i];
		while (item)
		{
			if (item->tag == ENV)
			{
				ft_putstr_fd(item->key, 1);
				ft_putstr_fd("=", 1);
				ft_putendl_fd(item->value, 1);
				//printf("%s=%s\n", item->key, item->value);
			}
			item = item->next;
		}
		i++;
	}
	return (0);
}
