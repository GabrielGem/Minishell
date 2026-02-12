/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:18:09 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/12 16:54:11 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "hashtable.h"
# include "structs.h"

void			free_shell(t_data *context);
void			free_tree(t_ast_node *tree);

char			*get_path(char *cmd, t_data *contexte);
char			*binary_search(char **path, char *cmd);
int				is_valid_executable(char *path);
int				valid_command(char *cmd);
int				file_exist(char *path);
int				exit_error(char *cmd, int code, t_data *context);

char			**concatenate(char **strs, char *join);

t_hash_table	*env_to_table(char **env);
char			**table_to_envp(t_hash_table *table);
t_hash_item		**table_for_array_of_items(t_hash_table *table, int count, \
				t_hash_type tag);
int				count_items_by_tag(t_hash_table *table, t_hash_type tag);
void			sort_array_of_items(t_hash_item **array, int count);
t_hash_item		**get_sorted_export_items(t_hash_table *table);

char			*extract_value(char *line);
char			*extract_key(char *line);

int				is_valid_identifier(char *str);
void			print_invalid_identifier(char *identifier);

#endif
