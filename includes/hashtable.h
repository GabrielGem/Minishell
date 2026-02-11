/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:30:06 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/11 17:56:06 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHTABLE_H
# define HASHTABLE_H

# include "libft.h"

# define INITIAL_SIZE 257

typedef enum s_hash_type
{
	ENV = 1,
	EXPORT,
	SET
}	t_hash_type;

typedef struct s_hash_item
{
	struct s_hash_item	*next;
	char				*key;
	char				*value;
	t_hash_type			tag;
}	t_hash_item;

typedef struct s_hash_table
{
	t_hash_item	**items;
	int			size;
	int			count;
}	t_hash_table;

t_hash_table	*create_table(int size);
t_hash_item		*hash_item(char *key, char *value, t_hash_type tag);
unsigned int	hash_function(char *key, int size);
int				hash_upsert(t_hash_table *table, char *key, char *value, \
				t_hash_type tag);
int				hash_update_tag(t_hash_table *table, char *key, \
				t_hash_type old_tag, t_hash_type new_tag);
char			*hash_search(t_hash_table *table, char *key, t_hash_type tag);
int				hash_delete(t_hash_table *table, char *key, t_hash_type tag);
void			destroy_item(t_hash_item *item);
void			destroy_table(t_hash_table *table);

#endif
