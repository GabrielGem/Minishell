/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 09:58:31 by mmaquine          #+#    #+#             */
/*   Updated: 2026/01/15 10:58:22 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ast_node	*build_tree_polimorphic(void);
static void	print_tree2(t_ast_node *root);

int	main(int argc __attribute__((unused)), char **argv __attribute__((unused)),\
	char **envp __attribute__((unused)))
{
	char		*line;
	t_ast_node	*root;

	while (1)
	{
		line = readline("$> ");
		root = build_tree_polimorphic();
		print_tree2(root);
		free(line);
	}
	// clean tree
	return (0);
}

static t_ast_node	*build_tree_polimorphic(void)
{
	//t_ast_node	*root;
	t_ast_node	*node1;
	//t_ast_node	*node2;
	//t_exec		*pipes;
	t_command	*cmd;
	t_command	*cmd2;

	//pipes = ft_calloc(sizeof(t_exec), 1);
	//pipes->type.base = NODE_PIPE;
	//int fd[2];
	//pipe(fd);
	//pipes->pipes = &fd;
	//pipes->stdin_backup = dup(STDIN_FILENO);
	//pipes->stdout_backup = dup(STDOUT_FILENO);
	//root = ft_calloc(sizeof(t_ast_node), 1);
	//root = (t_ast_node *)pipe;

	cmd = ft_calloc(sizeof(t_command), 1);
	cmd->type.base = NODE_COMMAND;
	cmd->args = ft_calloc(sizeof(char *), 3);
	cmd->args[0] = "/usr/bin/ls";
	cmd->args[1] = "ls";
	cmd->args[2] = NULL;
	//cmd->redirects = ft_lstnew(malloc(sizeof(t_redir)));
	//t_redir *redirect = ((t_redir *)cmd->redirects->content);
	//redirect->type = REDIN;
	//redirect->filename = "file1";
	node1 = ft_calloc(sizeof(t_ast_node), 1);
	node1 = (t_ast_node *)cmd;

	//cmd2 = ft_calloc(sizeof(t_command), 1);
	//cmd2->type.base = NODE_COMMAND;
	//cmd2->args = ft_calloc(sizeof(char *), 4);
	//cmd2->args[0] = "/usr/bin/wc";
	//cmd2->args[1] = "wc";
	//cmd2->args[2] = "-l";
	//cmd2->args[3] = NULL;
	//t_redir *redirect2 = ((t_redir *)cmd->redirects->content);
	//redirect2->type = REDOUT;
	//redirect2->filename = "file2";
	//node2 = ft_calloc(sizeof(t_ast_node), 1);
	//node2 = (t_ast_node *)cmd2;

	//root->left = (t_sheets *)node1;
	//root->right = (t_sheets *)node2;
	return (node1);
}

static void	print_tree2(t_ast_node *root)
{
	if (root == NULL)
		return ;
	if (root->type.base == NODE_PIPE)
	{
		ft_printf("PIPE:\n");
		print_tree2((t_ast_node *)root->left);
		print_tree2((t_ast_node *)root->right);
	}
	if (root->type.base == NODE_COMMAND)
	{
		ft_printf("  CMD:\n");
		char **args = ((t_command *)root)->args;
		if (args == NULL)
		{
			ft_printf("    Error: args is NULL\n");
			return ;
		}
		while (*args)
			ft_printf("  %s\n", *args++);
	}
}
