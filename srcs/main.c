/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 17:10:32 by gabrgarc          #+#    #+#             */
/*   Updated: 2025/12/24 14:18:09 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		print_env(char **env);
static void		print_table(t_hash_table *table);

int	main(int argc, char **argv, char **envp)
{
	t_hash_table 	*table;
	char			**env;
	char			**path;
	char			*temp;
	char			*binary;

	(void)argc;
	table = env_to_table(envp);
	print_table(table);
	env = table_to_env(table);
	if (!ft_strncmp(argv[1], "env", 4))
		print_env(env);
	ft_free_split(env);
	temp = hash_search(table, "PATH");
	path = ft_split(temp, ':');
	destroy_table(table);
	path = concatenate(path, "/");
	binary = binary_search(path, argv[2]);
	printf("%s\n", binary);
	ft_free_split(path);
	return (0);
}

static void	print_env(char **env)
{
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}

static void	print_table(t_hash_table *table)
{
	int			i;
	t_hash_item	*item;

	i = 0;
	while(i < table->size)
	{
		item = table->items[i];
		while (item)
		{
			printf("key: %s,\nvalue: %s\n", item->key, item->value);
			item = item->next;
		}
		i++;
	}
}
