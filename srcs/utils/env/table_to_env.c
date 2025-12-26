/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_to_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 16:29:26 by gabrgarc          #+#    #+#             */
/*   Updated: 2025/12/23 17:24:48 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_str(char *key, char *value);

char	**table_to_env(t_hash_table *table)
{
	char		**env;
	t_hash_item	*item;
	int			i;
	int			j;

	env = ft_calloc(sizeof(char *), table->count + 1);
	if (!env)
		return (NULL);
	env[table->count] = NULL;
	i = 0;
	j = 0;
	while (i < table->size)
	{
		item = table->items[i];
		while (item)
		{
			env[j] = get_env_str(item->key, item->value);
			j++;
			item = item->next;
		}
		i++;
	}
	return (env);
}

static char	*get_env_str(char *key, char *value)
{
	char	*temp;
	char	*str;

	temp = ft_strjoin(key, "=");
	str = ft_strjoin(temp, value);
	free(temp);
	return (str);
}
