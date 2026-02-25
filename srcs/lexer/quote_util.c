/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 16:15:30 by mmaquine          #+#    #+#             */
/*   Updated: 2026/02/24 23:47:36 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*/
char	is_quote_token(t_list *token, char tkn)
{
	char	*str;

	if (!token || !token->content)
		return (0);
	str = token->content;
	if (str[0] == tkn && str[ft_strlen(str) - 1] == tkn)
		return (1);
	return (0);
}

/*
Return the lower position in a quote bounded section of str.
*/
char	*find_bound_quote(char *str, char quote)
{
	char	*start;
	char	*end;

	start = ft_strchr(str, quote);
	end = ft_strrchr(str, quote);
	if (start && end && start < end)
		return (start);
	return (NULL);
}

static char	*first_bound_quote(char *str)
{
	char	*single;
	char	*doubleq;

	single = find_bound_quote(str, '\'');
	doubleq = find_bound_quote(str, '\"');
	if (single && doubleq)
	{
		if (single < doubleq)
			return (single);
		else
			return (doubleq);
	}
	if (single)
		return (single);
	if (doubleq)
		return (doubleq);
	return (NULL);
}

static	void	solve_while(char **src, char **start, char **end, char **new)
{
	t_quote_state	state;

	state = NORMAL;
	while (**src)
	{
		if (state == NORMAL)
		{
			if (*src == *start)
				state = IN_DOUBLE_QUOTE;
			append_char(new, **src);
		}
		else if (state == IN_DOUBLE_QUOTE)
		{
			if (*src == *end)
			{
				append_char(new, **src);
				state = NORMAL;
			}
			if (**src != **start)
				append_char(new, **src);
		}
		(*src)++;
	}
}

/*
Remove quotes by the same type if they are bounded.
*/
char	*remove_internal_quote(char *str)
{
	char			*start;
	char			*end;
	char			*src;
	char			*new;

	start = first_bound_quote(str);
	if (!start)
		return (str);
	end = ft_strrchr(start + 1, *start);
	if (!end || end <= start)
		return (str);
	new = NULL;
	src = str;
	solve_while(&src, &start, &end, &new);
	free(str);
	return (new);
}
