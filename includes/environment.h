/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 14:26:12 by gabrgarc          #+#    #+#             */
/*   Updated: 2025/12/24 14:46:11 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "hashtable.h"

char			*binary_search(char **path, char *cmd);
char		 	**concatenate(char **strs, char *join);
t_hash_table	*env_to_table(char **env);
int				is_valid_executable(char *path);
char			**table_to_env(t_hash_table *table);

#endif
