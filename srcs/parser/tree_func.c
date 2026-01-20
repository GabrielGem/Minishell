/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 11:00:59 by mmaquine          #+#    #+#             */
/*   Updated: 2026/01/19 11:41:04 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*initial_parser(char *line)
{
	char 	**split;
	t_list	*tokens;
	int		i;

	if (!line)
		return (NULL);
	split = ft_split(line, ' ');
	if(!split)
		return (NULL);
	i = 0;
	tokens = NULL;
	while (split[i])
	{
		ft_lstadd_back(&tokens, ft_lstnew(split[i]));
		i++;
	}
	free(split);
	free(line);
	return (tokens);
}

t_ast_node	*new(void)
{
	t_ast_node	*node;

	node = ft_calloc(1, sizeof(t_ast_node));
	if (!node)
		return (node);
	return (node);
}

// will print the linked list of tokens
static void	_print_list(t_list *node)
{
	while (node)
	{
		printf("%s\n", (char *)node->content);
		node = node->next;
	}
}

t_ast_node	*tokenizer(char *line, char **env)
{
	t_list	*tokens;

	(void)env;
	if (!line)
		return (NULL);
	if (!check_spaces(line))
	{
		free(line);
		return (NULL);
	}
	tokens = initial_parser(line);
	tokens = split_token(tokens, "|", NULL);
	tokens = split_token(tokens, ">>", NULL);
	tokens = split_token(tokens, "<<", NULL);
	tokens = split_token(tokens, ">", ">>");
	tokens = split_token(tokens, "<", "<<");
	tokens = split_token(tokens, "\'", NULL);
	tokens = split_token(tokens, "\"", NULL);
	_print_list(tokens);
	ft_lstclear(&tokens, free);
	return (NULL);
}

t_quote_mode	verify_quotes(char *line, char quote, t_quote_mode mode)
{
	while (line)
	{
		if (line == quote && quote == '\"' && mode == NORMAL_MODE)
			verify_quotes(++line, quote, IN_DOUBLE_QUOTE);
		if (line == quote && quote == '\"' && mode == IN_DOUBLE_QUOTE)
			verify_quotes(++line, quote, NORMAL_MODE);
		if (line == quote && quote == '\'' && mode == NORMAL_MODE)
			verify_quotes(++line, quote, IN_SINGLE_QUOTE);
		if (line == quote && quote == '\'' && mode == IN_SINGLE_QUOTE)
			verify_quotes(++line, quote, NORMAL_MODE);
		line++;
	}
	return (mode);
}
