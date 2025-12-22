/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 11:00:59 by mmaquine          #+#    #+#             */
/*   Updated: 2025/12/22 14:46:21 by mmaquine         ###   ########.fr       */
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

t_ast_node	*build_tree(char *line, char **env)
{
	char	**tokens;
	int		i = 0;

	(void)env;
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
