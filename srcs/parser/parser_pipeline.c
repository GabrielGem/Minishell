/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:01:25 by mmaquine          #+#    #+#             */
/*   Updated: 2026/02/14 16:29:33 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tests.h"

t_ast_node	*parse_pipeline(t_list **tokens, t_data *context)
{
	t_ast_node	*pipe_node;
	t_command	*left;

	left = parse_command(tokens, context);
	if(!left)
		return (NULL);
	if(*tokens && !ft_strcmp("|", (*tokens)->content))
	{
		pipe_node = ft_calloc(1, sizeof(t_ast_node));
		pipe_node->type.base = NODE_PIPE;
		pipe_node->left = (t_node *)left;
		*tokens = (*tokens)->next;
		pipe_node->right = (t_node *)parse_pipeline(tokens, context);
		return (pipe_node);
	}
	return ((t_ast_node *)left);
}

t_ast_node*	tree_build(char *line, t_data *context)
{
	t_list		*tokens;
	t_ast_node	*tree;

	tokens = NULL;
	tree = NULL;
	tokens = tokenizer(line);
	(void)context;
	if (!tokens)
		return (NULL);
	tree = parse_pipeline(&tokens, context);
	ft_print_ast(tree);
	ft_lstclear(&tokens, free);
	return (tree);
	//free_tree(tree);
}
