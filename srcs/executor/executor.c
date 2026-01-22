/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 13:14:12 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/01/21 17:40:57 by gabrgarc         ###   ########.fr       */
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

	if (root == NULL)
		return (0);
	ft = map[root->type.base];
	ft(root, context);
	return (context->exit_status);
}
