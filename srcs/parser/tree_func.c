/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 11:00:59 by mmaquine          #+#    #+#             */
/*   Updated: 2026/01/30 20:06:58 by mmaquine         ###   ########.fr       */
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
	if (check_spaces(line))
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

// static t_list	**helper_evaluate_quotes(t_list **token, char *str)
// {
// 	if (str && !ft_strlen(str))
// 	{
// 		free(str);
// 		str = NULL;
// 	}
// 	if (str)
// 		ft_lstadd_back(token, ft_lstnew(str));
// 	return (token);
// }

t_list	*evaluate_quotes(t_list *token, char *quote_pos)
{
	char	*lstr;
	char	*rstr;
	char	*mstr;
	char	*end;
	t_list	*new_token;

	new_token = NULL;
	end = ft_strchr(quote_pos + 1, *quote_pos);
	if (!end)
		return (token);
	lstr = ft_substr(token->content, 0, quote_pos - (char *)(token->content));
	mstr = ft_substr(token->content, quote_pos - (char *)(token->content),
		end - quote_pos + 1);
	rstr = ft_substr(token->content, end + 1 - (char *)(token->content),
		ft_strlen(end));
	if (lstr && !ft_strlen(lstr))
	{
		free(lstr);
		lstr = NULL;		
	}
	if (mstr && !ft_strlen(mstr))
	{
		free(mstr);
		mstr = NULL;
	}
	if (rstr && !ft_strlen(rstr))
	{
		free(rstr);
		rstr = NULL;
	}
	if (lstr)
		new_token = ft_lstnew(lstr);
	if (mstr)
		ft_lstadd_back(&new_token, ft_lstnew(mstr));
	if (rstr)
		ft_lstadd_back(&new_token, ft_lstnew(rstr));
	ft_lstdelone(token, free);
	return (new_token);
}

void	*resolve_quotes(t_list *tokens)
{
	char	*s_quote;
	char	*d_quote;
	t_list	*last;

	if (!tokens)
		return (NULL);
	while (tokens)
	{
		s_quote = ft_strchr(tokens->content, '\'');
		d_quote = ft_strchr(tokens->content, '\"');
		if (s_quote == d_quote || is_quote_token(tokens, '\'') 
			|| is_quote_token(tokens, '\"'))
		{
			tokens->next = tokens;
			continue ;
		}
		if (d_quote && d_quote < s_quote)
			last = evaluate_quotes(tokens, d_quote);
		else if (s_quote && s_quote < d_quote)
			last = evaluate_quotes(tokens, s_quote);
		tokens = last;
		tokens->next = tokens;
	}
	return (NULL); //corrigir
}

char	is_quote_token(t_list *token, char tkn)
{
	char	*str;

	if (!token || !token->content)
		return (0);
	str = token->content;
	if (str[0] == tkn || str[ft_strlen(str) - 1] == tkn)
		return (1);
	return (0);
}

/*
Add new tokens iten(s) list between existing tokens
*/
void	*insert_new_tokens(t_list *left, t_list *mid, t_list *right)
{
	ft_lstadd_after(left, mid);
	mid = ft_lstlast(mid);
	ft_lstadd_after(mid, right);
	return (ft_lstfirst(mid));
}