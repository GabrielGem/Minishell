/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 11:00:59 by mmaquine          #+#    #+#             */
/*   Updated: 2026/02/11 18:02:44 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_ast_node	*new(void)
{
	t_ast_node	*node;

	node = ft_calloc(1, sizeof(t_ast_node));
	if (!node)
		return (node);
	return (node);
}

t_ast_node	*build_tree(char *line)
{
	char	**tokens;
	int		i;

	i = 0;
	if (!line)
		return (NULL);
	tokens = ft_split(line, ' ');
	while (tokens[i])
	{
		printf("%s\n", tokens[i]);
		i++;
	}
	ft_free_split(tokens);
	return (NULL);
}
