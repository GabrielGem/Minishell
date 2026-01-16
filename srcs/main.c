/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 09:58:31 by mmaquine          #+#    #+#             */
/*   Updated: 2026/01/16 17:30:24 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ast_node	*build_tree_polimorphic(void);
static void			print_tree(t_ast_node *tree);
void				free_command(t_command *cmd);
void				free_tree(t_ast_node *tree);

int	main(int argc __attribute__((unused)), char **argv __attribute__((unused)),\
	char **envp)
{
	char	*line;
	t_data	context;

	context = (t_data){0};
	context.envp = envp;
	while (1)
	{
		line = readline("$> ");
		if (line == NULL)
			break ;
		context.root = build_tree_polimorphic();
		print_tree(context.root);
		executor(&context);
		free_tree(context.root);
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
	cmd->args[0] = ft_strdup("/usr/bin/ls");
	cmd->args[1] = ft_strdup("ls");
	cmd->args[2] = NULL;
	node1 = (t_ast_node *)cmd;
	return (node1);
}

static void	print_tree(t_ast_node *tree)
{
	if (tree == NULL)
		return ;
	if (tree->type.base == NODE_PIPE)
	{
		ft_printf("PIPE:\n");
		print_tree((t_ast_node *)tree->left);
		print_tree((t_ast_node *)tree->right);
	}
	if (tree->type.base == NODE_COMMAND)
	{
		ft_printf("  CMD:\n");
		char **args = ((t_command *)tree)->args;
		if (args == NULL)
		{
			ft_printf("    Error: args is NULL\n");
			return ;
		}
		while (*args)
			ft_printf("  %s\n", *args++);
	}
}

void	free_tree(t_ast_node *tree)
{
	if (tree == NULL)
		return ;
	//if (tree->type.base == NODE_COMMAND)
	//	free_pipe((t_exec *)tree);
	//free_tree((t_ast_node *)tree->left);
	//free_tree((t_ast_node *)tree->right);
	if (tree->type.base == NODE_COMMAND)
		free_command((t_command *)tree);
}

void	free_redir(void *redir)
{
	free(((t_redir *)redir)->filename);
}

void	free_command(t_command *cmd)
{
	ft_free_split(cmd->args);
	ft_lstclear(&cmd->redirects, free_redir);
	free(cmd);
}
