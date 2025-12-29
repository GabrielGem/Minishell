/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 11:00:59 by mmaquine          #+#    #+#             */
/*   Updated: 2025/12/29 17:04:26 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*new(void)
{
	t_ast_node	*node;

	node = ft_calloc(1, sizeof(t_ast_node));
	if (!node)
		return (node);
	return (node);
}

void	_print_list(t_list *node)
{
	while (node)
	{
		printf("%s\n", (char *)node->content);
		node = node->next;
	}
}

t_ast_node	*build_tree(char *line, char **env)
{
	t_list	*tokens;
	(void)env;
	if (!line)
		return (NULL);
	tokens = ft_lstnew(line);
	tokens = split_token(tokens, "|");
	tokens = split_token(tokens, ">");
	tokens = split_token(tokens, "<");
	tokens = split_token(tokens, ">>");
	tokens = split_token(tokens, "<<");
	_print_list(tokens);
	ft_lstclear(&tokens, free);
	return (NULL);
}
