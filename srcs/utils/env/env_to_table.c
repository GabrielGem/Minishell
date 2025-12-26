/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 12:30:00 by gabrgarc          #+#    #+#             */
/*   Updated: 2025/12/23 17:24:47 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_key(char *env_line);
static char	*extract_value(char *env_line);

t_hash_table	*env_to_table(char **env)
{
	t_hash_table	*table;
	char			*key;
	char			*value;
	int				i;

	if (!env)
		return (NULL);
	table = create_table(257);
	if (!table)
		return (NULL);
	i = 0;
	while (env[i])
	{
		key = extract_key(env[i]);
		value = extract_value(env[i]);
		if (key && value)
			hash_upsert(table, key, value);
		free(key);
		free(value);
		i++;
	}
	return (table);
}

static char	*extract_key(char *env_line)
{
	char	*equal_sign;
	char	*key;
	int		key_len;

	if (!env_line)
		return (NULL);
	equal_sign = ft_strchr(env_line, '=');
	if (!equal_sign)
	{
		key = ft_strdup(env_line);
		return (key);
	}
	key_len = equal_sign - env_line;
	key = ft_substr(env_line, 0, key_len);
	return (key);
}

static char	*extract_value(char *env_line)
{
	char	*equal_sign;
	char	*value;

	if (!env_line)
		return (NULL);
	equal_sign = ft_strchr(env_line, '=');
	if (!equal_sign)
	{
		value = ft_strdup("");
		return (value);
	}
	value = ft_strdup(equal_sign + 1);
	return (value);
}
