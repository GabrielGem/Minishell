/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:28:03 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/17 12:04:57 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_pipe_heredoc(t_ast_node *tree, t_data *context)
{
	int	count;

	count = 0;
	context->count_line += hunt_heredoc((t_ast_node *)tree->left, context);
	count += hunt_heredoc((t_ast_node *)tree->right, context);
	return (count);
}
