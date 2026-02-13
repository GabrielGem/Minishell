/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree_polimorphic.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 15:22:35 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/07 12:02:34 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*build_tree_polimorphic(void)
{
	t_command	*cmd;
	cmd = ft_calloc(1, sizeof(t_command));
	cmd->type.base = NODE_COMMAND;
	//cmd->is_builtin = B_EXPORT;
	cmd->args = ft_calloc(4, sizeof(char *));
	cmd->args[0] = ft_strdup("/usr/bin/ls");
	cmd->args[1] = ft_strdup("ls");
	cmd->args[2] = ft_strdup("-l");
	cmd->args[3] = NULL;

	t_command	*cmd2;
	cmd2 = ft_calloc(1, sizeof(t_command));
	cmd2->type.base = NODE_COMMAND;
	cmd2->args = ft_calloc(4, sizeof(char *));
	cmd2->args[0] = ft_strdup("/usr/bin/wc");
	cmd2->args[1] = ft_strdup("wc");
	cmd2->args[2] = ft_strdup("-l");
	cmd2->args[3] = NULL;

	//t_command	*cmd3;
	//cmd3 = ft_calloc(1, sizeof(t_command));
	//cmd3->type.base = NODE_COMMAND;
	//cmd3->args = ft_calloc(4, sizeof(char *));
	//cmd3->args[0] = ft_strdup("/usr/bin/wc");
	//cmd3->args[1] = ft_strdup("wc");
	//cmd3->args[2] = ft_strdup("-l");
	//cmd3->args[3] = NULL;

	t_redir	*redir;
	redir = ft_calloc(1, sizeof(t_redir));
	redir->type = REDOUT;
	redir->filename = ft_strdup("file1");
	ft_lstadd_back(&cmd->redirects, ft_lstnew(redir));

	t_redir	*redir2;
	redir2 = ft_calloc(1, sizeof(t_redir));
	redir2->type = REDIN;
	redir2->filename = ft_strdup("file1");
	ft_lstadd_back(&cmd2->redirects, ft_lstnew(redir2));

	t_ast_node	*pipe1;
	//t_ast_node	*pipe2;

	pipe1 = ft_calloc(1, sizeof(t_ast_node));
	pipe1->type.base = NODE_PIPE;
	pipe1->left = (t_node *)cmd;
	pipe1->right = (t_node *)cmd2;
	//pipe2 = ft_calloc(1, sizeof(t_ast_node));
	//pipe2->type.base = NODE_PIPE;
	//pipe2->left = (t_node *)pipe1;
	//pipe2->right = (t_node *)cmd3;
	return (pipe1);
}
