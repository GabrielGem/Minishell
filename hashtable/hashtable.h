/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 16:12:02 by gabrgarc          #+#    #+#             */
/*   Updated: 2025/12/21 14:53:55 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHTABLE_H
# define HASHTABLE_H

# include <stdlib.h>
# include "libft/libft.h"

typedef struct s_hash_item
{
	struct s_hash_item	*next;
	char				*key;
	char				*value;
}	t_hash_item;

typedef struct s_hash_table
{
	t_hash_item	**items;
	int			size;
	int			count;
}	t_hash_table;

t_hash_table	*create_table(int size);
t_hash_item		*hash_item(char *key, char *value);
unsigned int	hash_function(char *key, int size);
int				hash_upsert(t_hash_table *table, char *key, char *value);
char			*hash_search(t_hash_table *table, char *key);
int				hash_delete(t_hash_table *table, char *key);
void			destroy_item(t_hash_item *item);
void			destroy_table(t_hash_table *table);

#endif
