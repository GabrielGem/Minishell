/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 17:10:08 by mmaquine          #+#    #+#             */
/*   Updated: 2026/02/24 23:39:33 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Return 1 is string is bounded for any kind of quotes, 0 otherwise.
*/
char	is_single_or_double_quotes(t_list *token)
{
	return (is_quote_token(token, '\'') || is_quote_token(token, '\"'));
}

/*
Remove only quotes from ends.
*/
char	*remove_quote_from_ends(char *old)
{
	size_t	len;
	char	*new;

	if (!old)
		return (old);
	len = ft_strlen(old);
	new = ft_substr(old, 1, len - 2);
	free(old);
	return (new);
}

/*
Remove all quotes.
*/
char	*remove_all_quotes(char *old)
{
	char	*new;
	int		i;

	new = NULL;
	i = 0;
	if (!old)
		return (old);
	while (old[i])
	{
		if (old[i] != '\"' && old[i] != '\'')
			append_char(&new, old[i]);
		i++;
	}
	free(old);
	return (new);
}

/*
Remove quotation marks.
*/
void	remove_quotes(t_list *tokens)
{
	char	*dollar;

	while (tokens)
	{
		dollar = ft_strchr(tokens->content, '$');
		if (!is_single_or_double_quotes(tokens) && !dollar)
			tokens->content = remove_all_quotes(tokens->content);
		tokens = tokens->next;
	}
}

/*
Remove quotes mark from parameter list
*/
void	remove_param_quotes(t_list *tokens)
{
	while (tokens)
	{
		if (is_single_or_double_quotes(tokens))
		{
			tokens->content = remove_internal_quote(tokens->content);
			tokens->content = remove_quote_from_ends(tokens->content);
		}
		tokens = tokens->next;
	}
}
