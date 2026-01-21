/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 11:00:59 by mmaquine          #+#    #+#             */
/*   Updated: 2026/01/21 15:19:23 by mmaquine         ###   ########.fr       */
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
	_print_list(tokens);
	ft_lstclear(&tokens, free);
	return (NULL);
}

/*
	Return 1 if all quotes are closed, 0 otherwise
*/
int	check_quotes(char *line, char quote)
{
	int	mode;

	mode = 0;
	while (*line)
	{
		if (*line == quote)
			mode = !mode;
		line++;
	}
	return (mode);
}

t_list	*evaluate_quotes(t_list *token, char *quote)
{
	char	*start;
	char	*end;

	start = NULL;
	end = NULL;
	start = ft_strchr(token->content, quote);
	if (start)
		end = ft_strchr(start + 1, quote);
}

void	*resolve_quotes(t_list *tokens, char quote)
{
	char	*quote;
	char	*d_quote;

	if (!tokens)
		return (NULL);
	quote = NULL;
	d_quote = NULL;
	while (tokens)
	{
		quote = ft_strchr(tokens->content, '\'');
		d_quote = ft_strchr(tokens->content, '\"');
		if (quote == d_quote)
		{
			tokens->next = tokens;
			continue ;
		}
		if (d_quote && d_quote < quote)
			tokens = evaluate_quotes(tokens, d_quote);
		else if (quote && quote < d_quote)
			tokens = evaluate_quotes(tokens, quote);
		tokens->next = tokens;
	}
}
