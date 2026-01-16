/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 09:58:31 by mmaquine          #+#    #+#             */
/*   Updated: 2026/01/15 18:44:22 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ast_node	*build_tree_polimorphic(void);
static void			print_tree(t_ast_node *root);
void				free_command(t_node *leaf);

int	main(int argc __attribute__((unused)), char **argv __attribute__((unused)),\
	char **envp)
{
	char		*line;
	t_ast_node	*root;
	t_data		context;

	context = (t_data){0};
	context.envp = envp;
	while (1)
	{
		line = readline("$> ");
		if (line == NULL)
			break ;
		root = build_tree_polimorphic();
		print_tree(root);
		executor((t_node *)root, &context);
		free(line);
	}
	free(line);
	return (0);
}

static t_ast_node	*build_tree_polimorphic(void)
{
	t_ast_node	*node1;
	t_command	*cmd;

	cmd = ft_calloc(sizeof(t_command), 1);
	cmd->type.base = NODE_COMMAND;
	cmd->args = ft_calloc(sizeof(char *), 3);
	cmd->args[0] = "/usr/bin/ls";
	cmd->args[1] = "ls";
	cmd->args[2] = NULL;
	node1 = (t_ast_node *)cmd;
	return (node1);
}

static void	print_tree(t_ast_node *root)
{
	if (root == NULL)
		return ;
	if (root->type.base == NODE_PIPE)
	{
		ft_printf("PIPE:\n");
		print_tree((t_ast_node *)root->left);
		print_tree((t_ast_node *)root->right);
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

void	free_command(t_command *cmd)
{
	ft_free_split(cmd->args);
	ft_lstclear(cmd->redirects, &free_redir);
}

void	free_redir(void *redir)
{
	free(redir->filename);
}
