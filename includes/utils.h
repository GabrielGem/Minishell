/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:18:09 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/01/29 15:24:51 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include "hashtable.h"
#include "structs.h"

void			free_context(t_data *context);
void			free_tree(t_ast_node *tree);

char			*binary_search(char **path, char *cmd);
char			**concatenate(char **strs, char *join);
t_hash_table	*env_to_table(char **env);
int				is_valid_executable(char *path);
char			**table_to_env(t_hash_table *table);

#endif
