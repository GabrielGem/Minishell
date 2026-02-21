/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 14:38:08 by mmaquine          #+#    #+#             */
/*   Updated: 2026/02/21 16:17:58 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	is_builtin(char *cmd)
{
	if (!cmd)
		return (EMPTY);
	if (!ft_strcmp(cmd, "echo"))
		return (ECHO);
	if (!ft_strcmp(cmd, "cd"))
		return (CD);
	if (!ft_strcmp(cmd, "pwd"))
		return (PWD);
	if (!ft_strcmp(cmd, "export"))
		return (B_EXPORT);
	if (!ft_strcmp(cmd, "unset"))
		return (UNSET);
	if (!ft_strcmp(cmd, "env"))
		return (B_ENV);
	if (!ft_strcmp(cmd, "exit"))
		return (EXIT);
	return (0);
}

t_list	*add_tokens(char *content, char *token_found, char *token)
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
	t_list	*head;
	size_t	len;

	head = tokens;
	while (tokens)
	{
		tkn = ft_strnstr(tokens->content, token, ft_strlen(tokens->content));
		len = ft_strlen(tkn);
		if (tkn && ft_strcmp(tkn, forbid) 
			&& (ft_strlen(token) != len || (ft_strlen(tokens->content) != len))
			&& !is_single_or_double_quotes(tokens))
		{
			new_tokens = add_tokens(tokens->content, tkn, token);
			insert_new_tokens(&head, tokens->prev, new_tokens, tokens->next);
 			ft_lstdelone(tokens, free);
			tokens = new_tokens;
			continue ;
		}
		tokens = tokens->next;
	}
	return (head);
}

void	print_tokens(t_list	*tokens)
{
	if (!tokens)
		return ;
	while (tokens)
	{
		ft_printf("%s\n", tokens->content);
		tokens = tokens->next;
	}
}
