/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 14:38:08 by mmaquine          #+#    #+#             */
/*   Updated: 2026/01/14 15:49:44 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo")
		|| ft_strcmp(cmd, "cd")
		|| ft_strcmp(cmd, "pwd")
		|| ft_strcmp(cmd, "export")
		|| ft_strcmp(cmd, "unset")
		|| ft_strcmp(cmd, "env")
		|| ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

static t_list *add_tokens(char *content, char *token_found)
{
	t_list	*ltkn;
	char	*lstr;
	char	*rstr;

	lstr = ft_substr(content, 0, token_found - content);
	rstr = ft_substr(content, token_found - content + 1, ft_strlen(content));
	if (!ft_strlen(lstr))
	{
		free(lstr);
		lstr = NULL;
	}
	if (!ft_strlen(rstr))
	{
		free(rstr);
		rstr = NULL;
	}
	if (lstr)
		ltkn = ft_lstnew(lstr);
	ft_lstadd_back(&ltkn, ft_lstnew(ft_strdup(token_found)));
	if (rstr)
		ft_lstadd_back(&ltkn, ft_lstnew(rstr));
	return (ltkn);
}

/*
When finding a token create its token and
*/
void	*split_token(t_list *tokens, char *token)
{
	char	*tkn;
	t_list	*ltkn;

	while(tokens)
	{
		tkn = ft_strnstr(tokens->content, token, ft_strlen(tokens->content));
		if (tkn)
		{
			ltkn = add_tokens(tokens->content, tkn);
			if (tokens->prev)
			{
				tokens->prev->next = ltkn;
				ltkn->prev = tokens->prev;
			}
			(ft_lstlast(ltkn))->next = tokens->next;
			if (tokens->next)
				tokens->next->prev = (ft_lstlast(ltkn));
			ft_lstdelone(tokens, free);
			tokens = ft_lstfirst(ltkn);
		}
		tokens = tokens->next;
	}
	return (ft_lstfirst(ltkn));
}
