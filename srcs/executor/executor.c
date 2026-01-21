/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 13:14:12 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/01/21 16:48:47 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor(t_data *context)
{
	t_handle		ft;
	static t_handle	map[2] = {
		&handle_command,
		&handle_pipe
	};

	if (context->root == NULL)
		return (0);
	ft = map[context->root->type.base];
	ft(context->root, context);
	return (context->exit_status);
}
