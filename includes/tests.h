/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 15:57:57 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/22 13:28:12 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

void		ft_print_ast(t_ast_node *root);
void		print_tree(t_ast_node *tree);
void		print_hash_table(t_hash_table *table);
t_ast_node	*build_tree_polimorphic(void);

#endif
