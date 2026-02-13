/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 17:49:36 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/01/31 17:17:27 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_args(t_hash_table *table, char **args);
static void	export_variable(t_hash_table *table, char *arg);
static void	print_export(t_hash_table *table);

int	b_export(t_data *context, char **args)
{
	int	status;

	if (args[1] == NULL)
	{
		print_export(context->env);
		return (0);
	}
	status = export_args(context->env, args);
	return (status);
}

static int	export_args(t_hash_table *table, char **args)
{
	int	i;
	int	exit_status;

	i = 1;
	exit_status = 0;
	while (args[i])
	{
		if (is_valid_identifier(args[i]))
			export_variable(table, args[i]);
		else
		{
			print_invalid_identifier(args[i]);
			exit_status = 1;
		}
		i++;
	}
	return (exit_status);
}

static void	export_variable(t_hash_table *table, char *arg)
{
	char	*key;
	char	*value;

	key = extract_key(arg);
	value = extract_value(arg);
	if (value)
		hash_upsert(table, key, value, ENV);
	else if (!hash_search(table, key, ENV))
		hash_upsert(table, key, NULL, EXPORT);
	free(key);
	free(value);
}

static void	print_export(t_hash_table *table)
{
	t_hash_item	**items;
	int			i;

	items = get_sorted_export_items(table);
	if (!items)
		return ;
	i = 0;
	while (items[i])
	{
		if (ft_strcmp(items[i]->key, "_") != 0)
		{
			printf("declare -x ");
			if (items[i]->value == NULL)
				printf("%s\n", items[i]->key);
			else
				printf("%s=\"%s\"\n", items[i]->key, items[i]->value);
		}
		i++;
	}
	free(items);
}
