/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 14:38:08 by mmaquine          #+#    #+#             */
/*   Updated: 2026/01/31 16:07:30 by mmaquine         ###   ########.fr       */
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

t_list *add_tokens(char *content, char *token_found, char *token)
{
	t_list	*ltkn;
	char	*lstr;
	char	*rstr;

	ltkn = NULL;
	lstr = ft_substr(content, 0, token_found - content);
	rstr = ft_substr(content, token_found - content + ft_strlen(token),
		ft_strlen(content));
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
	ft_lstadd_back(&ltkn, ft_lstnew(ft_strdup(token)));
	if (rstr)
		ft_lstadd_back(&ltkn, ft_lstnew(rstr));
	return (ltkn);
}

/*
When finding a token create its token and...
*/
void	*split_token(t_list *tokens, char *token, char *forbid)
{
	char	*tkn;
	t_list	*new_tokens;
	t_list	*last;

	while(tokens)
	{
		tkn = ft_strnstr(tokens->content, token, ft_strlen(tokens->content));
		if (tkn && (ft_strlen(token) != ft_strlen(tkn)
			|| (ft_strlen(tokens->content) != ft_strlen(tkn)))
			&& ft_strcmp(tkn, forbid))
		{
			new_tokens = add_tokens(tokens->content, tkn, token);
			if (tokens->prev)
			{
				tokens->prev->next = new_tokens;
				new_tokens->prev = tokens->prev;
			}
			(ft_lstlast(new_tokens))->next = tokens->next;
			if (tokens->next)
				tokens->next->prev = (ft_lstlast(new_tokens));
			ft_lstdelone(tokens, free);
			tokens = ft_lstfirst(new_tokens);
			//tokens = insert_new_tokens(tokens->prev, new_tokens, tokens->next);
		}
		last = tokens;
		tokens = tokens->next;
	}
	return (ft_lstfirst(last));
}
