/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 09:21:05 by mmaquine          #+#    #+#             */
/*   Updated: 2026/02/06 14:55:36 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*str_tok(t_list *token, char sep)
{
	char	**split;
	t_list	*new_list;
	int		i;

	new_list = NULL;
	split = ft_split(token->content, sep);
	if (!split)
		return (new_list);
	i = -1;
	while (split[++i])
		ft_lstadd_back(&new_list, ft_lstnew(split[i]));
	free(split);
	return (new_list);
}

t_list	*remove_spaces(t_list *tokens)
{
	t_list	*start;
	t_list	*new_list;
	char	*space;

	if (!tokens)
		return (tokens);
	start = tokens;
	while (tokens)
	{
		space = ft_strchr(tokens->content, ' ');
		if (!(is_quote_token(tokens, '\'') || is_quote_token(tokens, '\"'))
			&& space)
		{
			new_list = str_tok(tokens, ' ');
			if (new_list)
			{
				insert_new_tokens(&start, tokens->prev, new_list, tokens->next);
				ft_lstdelone(tokens, free);
				tokens = new_list;
			}
		}
		tokens = tokens->next;
	}
	return (ft_lstfirst(start));
}
