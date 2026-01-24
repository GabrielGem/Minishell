/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 09:58:31 by mmaquine          #+#    #+#             */
/*   Updated: 2026/01/24 18:10:03 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ast_node	*build_tree_polimorphic(void);
static void			print_tree(t_ast_node *tree);

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
		executor(context.root, &context);
		free_context(&context);
		free(line);
	}
	return (0);
}

static t_ast_node	*build_tree_polimorphic(void)
{
	t_command	*cmd;
	cmd = ft_calloc(1, sizeof(t_command));
	cmd->type.base = NODE_COMMAND;
	cmd->args = ft_calloc(4, sizeof(char *));
	cmd->args[0] = ft_strdup("/usr/bin/ls");
	cmd->args[1] = ft_strdup("ls");
	cmd->args[2] = ft_strdup("-l");
	cmd->args[3] = NULL;

	t_command	*cmd2;
	cmd2 = ft_calloc(1, sizeof(t_command));
	cmd2->type.base = NODE_COMMAND;
	cmd2->args = ft_calloc(4, sizeof(char *));
	cmd2->args[0] = ft_strdup("/usr/bin/grep");
	cmd2->args[1] = ft_strdup("grep");
	cmd2->args[2] = ft_strdup("^d");
	cmd2->args[3] = NULL;

	//t_command	*cmd3;
	//cmd3 = ft_calloc(1, sizeof(t_command));
	//cmd3->type.base = NODE_COMMAND;
	//cmd3->args = ft_calloc(4, sizeof(char *));
	//cmd3->args[0] = ft_strdup("/usr/bin/wc");
	//cmd3->args[1] = ft_strdup("wc");
	//cmd3->args[2] = ft_strdup("-l");
	//cmd3->args[3] = NULL;

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
