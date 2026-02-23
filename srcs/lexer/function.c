/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 14:38:08 by mmaquine          #+#    #+#             */
/*   Updated: 2026/02/23 16:28:09 by mmaquine         ###   ########.fr       */
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
Expands all variables (strings starting with $) in a string token.
Returns a new string with all variables replaced with their values.
*/
char	*expand_all_vars(char *old, t_data *context)
{
	t_list	*lst;
	char	*new;

	if(!old)
		return (old);
	lst = ft_lstnew(old);
	lst->next = NULL;
	lst->prev = NULL;
	lst = expand_token(lst, context);
	new = lst->content;
	free(lst);
	return (new);
}

/*
Print the list of tokens
*/
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
