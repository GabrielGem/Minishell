/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 15:57:57 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/06 16:07:11 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

void		free_context(t_data *data);
t_data		*init_shell(char **envp);
void		print_tree(t_ast_node *tree);
void		print_hash_table(t_hash_table *table);
t_ast_node	*build_tree_polimorphic(void);
void		close_fd(void *fd);
void		close_pid(void *pid);

#endif
