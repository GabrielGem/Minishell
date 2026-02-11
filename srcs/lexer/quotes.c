/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 13:20:38 by mmaquine          #+#    #+#             */
/*   Updated: 2026/02/04 09:33:52 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	helper_evaluate_quotes(t_list **token, char *str)
{
	if (str && !ft_strlen(str))
	{
		free(str);
		str = NULL;
	}
	if (str)
		ft_lstadd_back(token, ft_lstnew(str));
}

static t_list	*evaluate_quotes(t_list *token, char *quote_pos)
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
	helper_evaluate_quotes(&new_token, lstr);
	helper_evaluate_quotes(&new_token, mstr);
	helper_evaluate_quotes(&new_token, rstr);
	insert_new_tokens(NULL, token->prev, new_token, token->next);
	ft_lstdelone(token, free);
	return (new_token);
}

static t_list	*help_solve_quote(t_list *tokens, t_list **first, t_list *last)
{
	if (last)
	{
		if (!last->prev)
			*first = last;
		return (last);
	}
	else
		return (tokens->next);
}

static	t_list	*if_quotes(t_list *tokens, char *d_quote, char *s_quote)
{
	t_list	*last;

	last = NULL;
	if ((d_quote && d_quote < s_quote) || (!s_quote && d_quote))
		last = evaluate_quotes(tokens, d_quote);
	else if ((s_quote && s_quote < d_quote) || (!d_quote && s_quote))
		last = evaluate_quotes(tokens, s_quote);
	return (last);
}

t_list	*resolve_quotes(t_list *tokens)
{
	char	*s_quote;
	char	*d_quote;
	t_list	*last;
	t_list	*first;

	if (!tokens)
		return (NULL);
	first = tokens;
	while (tokens)
	{
		s_quote = ft_strchr(tokens->content, '\'');
		d_quote = ft_strchr(tokens->content, '\"');
		if (s_quote == d_quote || is_quote_token(tokens, '\'')
			|| is_quote_token(tokens, '\"'))
		{
			tokens = tokens->next;
			continue ;
		}
		last = if_quotes(tokens, d_quote, s_quote);
		tokens = help_solve_quote(tokens, &first, last);
	}
	return (first);
}
