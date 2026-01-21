/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 09:58:31 by mmaquine          #+#    #+#             */
/*   Updated: 2026/01/21 16:56:36 by gabrgarc         ###   ########.fr       */
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
	t_ast_node	*root;

	t_command	*cmd;
	cmd = ft_calloc(1, sizeof(t_command));
	cmd->type.base = NODE_COMMAND;
	cmd->args = ft_calloc(4, sizeof(char *));
	cmd->args[0] = ft_strdup("/usr/bin/ls");
	cmd->args[1] = ft_strdup("ls");
	cmd->args[2] = NULL;

	t_command	*cmd2;
	cmd2 = ft_calloc(1, sizeof(t_command));
	cmd2->type.base = NODE_COMMAND;
	cmd2->args = ft_calloc(4, sizeof(char *));
	cmd2->args[0] = ft_strdup("/usr/bin/wc");
	cmd2->args[1] = ft_strdup("wc");
	cmd2->args[2] = ft_strdup("-l");
	cmd2->args[3] = NULL;

	//t_redir	*redir;
	//redir = ft_calloc(1, sizeof(t_redir));
	//redir->type = REDOUT;
	//redir->filename = ft_strdup("file1");
	//ft_lstadd_back(&cmd->redirects, ft_lstnew(redir));

	//t_redir	*redir2;
	//redir2 = ft_calloc(1, sizeof(t_redir));
	//redir2->type = REDIN;
	//redir2->filename = ft_strdup("infile");
	//ft_lstadd_back(&cmd->redirects, ft_lstnew(redir2));

	root = ft_calloc(1, sizeof(t_ast_node *));
	root->type.base = NODE_PIPE;
	root->left = (t_node *)cmd;
	root->right = (t_node *)cmd2;
	return (root);
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
		t_command	*cmd = (t_command *)tree;
		t_list		*node = cmd->redirects;
		char 		**args = cmd->args;
		t_redir 	*red;

		ft_printf("  CMD:\n");
		if (args != NULL)
			while (*args)
				ft_printf("\t%s\n", *args++);
		if (node)
		{
			while (node)
			{
				red = (t_redir *)node->content;
				ft_putendl_fd(red->filename, 1);
				node = node->next;
			}
		}
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
	free(redir);
}

void	free_command(t_command *cmd)
{
	ft_free_split(cmd->args);
	ft_lstclear(&cmd->redirects, free_redir);
	free(cmd);
}
