/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hunt_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 10:25:43 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/16 18:39:00 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	hunt_heredoc(t_ast_node *tree, t_data *context)
{
	t_handle		ft;
	static t_handle	map[2] = {
		&handle_command_heredoc,
		&handle_pipe_heredoc
	};

	if (tree == NULL)
		return ;
	ft = map[tree->type.base];
	ft(tree, context);
	return ;
}
