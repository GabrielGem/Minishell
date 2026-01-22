/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 21:18:57 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/01/21 21:19:47 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_redir(void *redir);
static void	free_command(t_command *cmd);

void	free_tree(t_ast_node *tree)
{
	if (tree == NULL)
		return ;
	if (tree->type.base == NODE_PIPE)
	{
		free_tree((t_ast_node *)tree->left);
		free_tree((t_ast_node *)tree->right);
		free(tree);
	}
	else
		free_command((t_command *)tree);
}

static void	free_redir(void *redir)
{
	free(((t_redir *)redir)->filename);
	free(redir);
}

static void	free_command(t_command *cmd)
{
	ft_free_split(cmd->args);
	if (cmd->redirects)
		ft_lstclear(&cmd->redirects, free_redir);
	free(cmd);
}
