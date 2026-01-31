/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 12:30:00 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/01/31 17:15:05 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_hash_table	*env_to_table(char **env)
{
	t_hash_table	*table;
	char			*key;
	char			*value;
	int				i;

	if (!env)
		return (NULL);
	table = create_table(INITIAL_SIZE);
	if (!table)
		return (NULL);
	i = 0;
	while (env[i])
	{
		key = extract_key(env[i]);
		value = extract_value(env[i]);
		if (key && value)
			hash_upsert(table, key, value, ENV);
		free(key);
		free(value);
		i++;
	}
	return (table);
}
