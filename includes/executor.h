/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:47:46 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/11 18:38:26 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "libft.h"

typedef int	(*t_handle)(t_ast_node *leaf, t_data *context);

int		executor(t_ast_node *root, t_data *context);
int		handle_command(t_ast_node *leaf, t_data *context);
int		handle_command_fd(t_ast_node *leaf, int input_fd, int output_fd, \
		t_data *context);
int		*handle_redirs(t_list *lst);
int		handle_pipe(t_ast_node *leaf, t_data *context);

int		wait_processes(t_list *pids);

void	setup_pipe(int input_fd, int output_fd);
void	setup_fd(int new_fd, int old_fd);
void	restore_fd(t_data *context);

#endif
