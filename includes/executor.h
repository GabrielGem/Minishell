/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:47:46 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/01/16 11:23:25 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "libft.h"

typedef int	(*t_handle)(t_ast_node *leaf, t_data *context);

int	*handle_redirs(t_list *lst);
int	executor(t_data *context);
int	handle_command(t_ast_node *leaf, t_data *context);

#endif
