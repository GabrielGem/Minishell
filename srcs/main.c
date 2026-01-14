/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 09:58:31 by mmaquine          #+#    #+#             */
/*   Updated: 2026/01/14 15:50:59 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void			print_tree(t_ast_node *root);
static t_ast_node	*build_pseudo_tree(void);

int	main(int argc __attribute__((unused)), char **argv __attribute__((unused)),\
	char **envp __attribute__((unused)))
{
	char		*line;
	t_ast_node	*root;

	line = readline("$> ");
	while (line)
	{
		root = build_pseudo_tree();
		print_tree(root);
		free(line);
		line = readline("$> ");
	}
	// clean tree
	return (0);
}

static t_ast_node	*build_pseudo_tree(void)
{
	t_ast_node	*root;
	t_ast_node	*node1;
	t_ast_node	*node2;
	t_exec		*pipe_cmd;
	t_command	*cmd;
	t_command	*cmd2;

	root = ft_calloc(sizeof(t_ast_node *), 1);
	node1 = ft_calloc(sizeof(t_ast_node *), 1);
	node2 = ft_calloc(sizeof(t_ast_node *), 1);
	pipe_cmd = ft_calloc(sizeof(t_exec *), 1);
	cmd = ft_calloc(sizeof(t_command *), 1);
	cmd2 = ft_calloc(sizeof(t_command *), 1);

	int	fds[2];
	pipe(fds);
	*(pipe_cmd->pipes) = fds;
	pipe_cmd->stdin_backup = dup(STDIN_FILENO);
	pipe_cmd->stdout_backup = dup(STDOUT_FILENO);
	root->type = NODE_PIPE;
	root->param = pipe_cmd;

	cmd->args = ft_calloc(sizeof(char *), 4);
	cmd->args[0] = "/usr/bin/grep";
	cmd->args[1] = "grep";
	cmd->args[2] = "a";
	cmd->args[3] = NULL;
	cmd->redirects = ft_lstnew(malloc(sizeof(t_redir)));
	((t_redir *)cmd->redirects->content)->type = REDIN;
	((t_redir *)cmd->redirects->content)->filename = "file1";
	node1->type = NODE_COMMAND;
	node1->param = cmd;
	node1->left = NULL;
	node1->right = NULL;

	cmd2->args = ft_calloc(sizeof(char *), 4);
	cmd2->args[0] = "/usr/bin/wc";
	cmd2->args[1] = "wc";
	cmd2->args[2] = "-l";
	cmd2->args[3] = NULL;
	cmd2->redirects = ft_lstnew(malloc(sizeof(t_redir)));
	((t_redir *)cmd2->redirects->content)->type = REDOUT;
	((t_redir *)cmd2->redirects->content)->filename = "file2";
	node2->type = NODE_COMMAND;
	node2->param = cmd2;
	node2->left = NULL;
	node2->right = NULL;

	root->left = node1;
	root->right = node2;
	return (root);
}

static t_ast_node	*build_tree_polimorphic(void)
{
	t_ast_node	*root;
	t_command	*cmd;
	
	root = ft_calloc(sizeof(t_ast_node), 1);
	root->type = NODE_PIPE;

	
}

static void	print_tree(t_ast_node *root)
{
	if (root != NULL)
	{
		if (root->type == NODE_PIPE)
		{
			ft_printf("PIPE:\n");
			ft_printf("  %d, %d\n", ((t_exec *)root->param)->pipes[0],\
									((t_exec *)root->param)->pipes[1]);
		}
		if (root->type == NODE_COMMAND)
		{
			ft_printf("CMD:\n");
			char	**args = ((t_command *)root->param)->args;
			while (*args)
				ft_printf("  %s\n", *args++);
			t_command *cmd = (t_command *)root->param;
			ft_printf("  %s\n", ((t_redir *)cmd->redirects->content)->filename);
		}
		print_tree(root->left);
		print_tree(root->right);
	}
	return ;
}
