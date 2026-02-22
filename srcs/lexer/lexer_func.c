/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 11:00:59 by mmaquine          #+#    #+#             */
/*   Updated: 2026/02/22 17:46:33 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Add content to end of list and update counter
*/
static void	add_to_list(t_list **l, char **new, char *token_to_add)
{
	if (*new)
	{
		ft_lstadd_back(l, ft_lstnew(ft_strdup(*new)));
		free(*new);
		*new = NULL;
	}
	if (token_to_add)
		ft_lstadd_back(l, ft_lstnew(ft_strdup(token_to_add)));
}

/*
Update state and append char to string.
*/
static	t_quote_state	update_state(char **new, char append, t_quote_state st)
{
	append_char(new, append);
	return (st);
}

static void	state_quote(char token_state, char token, t_quote_state *st, \
	char **new)
{
	if (token == token_state)
		*st = update_state(new, token, NORMAL);
	else
		append_char(new, token);
}

static	void	state_normal(t_quote_state *state, char *token, \
	t_list **list, char **new)
{
	if (ft_isspace(*token))
		add_to_list(list, new, NULL);
	else if (*token == '\'')
		*state = update_state(new, *token, IN_SINGLE_QUOTE);
	else if (*token == '\"')
		*state = update_state(new, *token, IN_DOUBLE_QUOTE);
	else if (*token == '<' && token[1] == '<')
		add_to_list(list, new, "<<");
	else if (*token == '>' && token[1] == '>')
		add_to_list(list, new, ">>");
	else if (*token == '|')
		add_to_list(list, new, "|");
	else if (*token == '>')
		add_to_list(list, new, ">");
	else if (*token == '<')
		add_to_list(list, new, "<");
	else
		append_char(new, *token);
}

t_list	*initial_parser(char *token)
{
	t_quote_state	state;
	t_list			*lst;
	char			*current;
	char			*new;

	state = NORMAL;
	new = NULL;
	lst = NULL;
	current = token;
	while (*current)
	{
		if (state == NORMAL)
			state_normal(&state, current, &lst, &new);
		else if (state == IN_SINGLE_QUOTE)
			state_quote('\'', *current, &state, &new);
		else if (state == IN_DOUBLE_QUOTE)
			state_quote('\"', *current, &state, &new);
		current++;
	}
	add_to_list(&lst, &new, NULL);
	free(token);
	return (lst);
}
