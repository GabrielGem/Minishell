/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 13:14:12 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/17 11:20:43 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor(t_ast_node *root, t_data *context)
{
	t_handle		ft;
	static t_handle	map[2] = {
		&handle_command,
		&handle_pipe
	};
	int				exit_status;

	if (root == NULL)
		return (0);
	ft = map[root->type.base];
	exit_status = ft(root, context);
	return (exit_status);
}
