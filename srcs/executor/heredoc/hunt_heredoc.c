/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hunt_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 10:25:43 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/17 11:02:36 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	hunt_heredoc(t_ast_node *tree, t_data *context)
{
	int				count;
	t_handle		ft;
	static t_handle	map[2] = {
		&handle_command_heredoc,
		&handle_pipe_heredoc
	};

	if (tree == NULL)
		return (0);
	ft = map[tree->type.base];
	count = ft(tree, context);
	return (count);
}
