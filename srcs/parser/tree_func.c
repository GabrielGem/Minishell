/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 11:00:59 by mmaquine          #+#    #+#             */
/*   Updated: 2026/01/26 14:48:13 by mmaquine         ###   ########.fr       */
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


t_list	*evaluate_quotes(t_list *token, char *quote_pos)
{
	char	*lstr;
	char	*rstr;
	char	*mstr;
	char	*end;

	end = ft_strchr(quote_pos + 1, *quote_pos);
	if (!end)
		return (token);
	lstr = ft_substr(token->content, 0, quote_pos - (char *)(token->content));
	mstr = ft_substr(token->content, quote_pos - (char *)(token->content),
		end - quote_pos + 1);
	rstr = ft_substr(token->content, end + 1 - (char *)(token->content),
		ft_strlen(end));
	if (lstr && ft_strlen)
	return (token);
}

void	*resolve_quotes(t_list *tokens)
{
	char	*s_quote;
	char	*d_quote;

	if (!tokens)
		return (NULL);
	s_quote = NULL;
	d_quote = NULL;
	while (tokens)
	{
		s_quote = ft_strchr(tokens->content, '\'');
		d_quote = ft_strchr(tokens->content, '\"');
		if (s_quote == d_quote)
		{
			tokens->next = tokens;
			continue ;
		}
		if (d_quote && d_quote < s_quote)
			tokens = evaluate_quotes(tokens, d_quote);
		else if (s_quote && s_quote < d_quote)
			tokens = evaluate_quotes(tokens, s_quote);
		tokens->next = tokens;
	}
	return (NULL); //corrigir
}
