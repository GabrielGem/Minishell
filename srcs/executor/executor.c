/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 13:14:12 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/01/15 17:41:49 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor(t_node *leaf, t_data *context)
{
	t_handle		ft;
	static t_handle	map[2] = {
		//&handle_pipe,
		&handle_command
	};

	if (leaf == NULL)
		return (0);
	ft = map[leaf->base];
	ft(leaf, context);
	return (context->exit_status);
}
