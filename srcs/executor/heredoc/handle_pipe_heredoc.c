/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:28:03 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/16 15:34:34 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_pipe_heredoc(t_ast_node *tree, t_data *context)
{
	hunt_heredoc((t_ast_node *)tree->left, context);
	hunt_heredoc((t_ast_node *)tree->right, context);
	return (0);
}
