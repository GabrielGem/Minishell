/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 14:38:08 by mmaquine          #+#    #+#             */
/*   Updated: 2025/12/26 17:30:25 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") ||
		ft_strcmp(cmd, "cd") ||
		ft_strcmp(cmd, "pwd") ||
		ft_strcmp(cmd, "export") ||
		ft_strcmp(cmd, "unset") ||
		ft_strcmp(cmd, "env") ||
		ft_strcmp(cmd, "exit"))
		return (1);
		
	return (0);
}

/*
When finding a token create its token and
*/
void	split_token(t_list *tokens, char *token)
{
	char	*tkn;
	char	*lstr;
	char	*rstr;
	// t_list	*ltkn;

	while(tokens)
	{
		tkn = ft_strnstr(tokens->content, token, ft_strlen(tokens->content));
		if (tkn)
		{
			lstr = ft_substr(tokens->content, 0, tkn - (char *)tokens->content);
			rstr = ft_substr(tokens->content, tkn - (char *)tokens->content + 1,
				ft_strlen(tokens->content));
			// ltkn = ft_lstnew(lstr);
			// ft_lstadd_front(&ltkn, ft_lstnew(token));
			// if (ltkn->next)
			// 	ltkn = ltkn->next;
			// ft_lstadd_front(&ltkn, ft_lstnew(rstr));
			// if (tokens->prev)
			// 	tokens->prev->next = ltkn;
		}
		tokens = tokens->next;
	}
}
