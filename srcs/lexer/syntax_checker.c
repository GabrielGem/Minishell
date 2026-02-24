/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 17:51:35 by mmaquine          #+#    #+#             */
/*   Updated: 2026/02/23 19:33:49 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	is_heredoc_valid(t_list *tokens)
{
	if (ft_strcmp(tokens->content, "<<"))
		return (1);
	
}

/*
Check if commands is syntax is correct to be executed.
Returns 1 if it is ok, o otherwise
*/
char	is_command_valid(t_list	*tokens, t_data *context)
{
	if (!tokens)
		return (0);
	if (!ft_strcmp(tokens->content, "|"))
	{
		ft_printf("syntax error near unexpected token '|'\n");
		context->exit_status = 2;
		return (0);
	}
	while (tokens)
	{
		if (!ft_strcmp(tokens->content, "|"))
		{
			if (!tokens->next)
			{
				ft_printf("syntax error near unexpected token 'newline'\n");
				context->exit_status = 2;
				return (0);
			}
			if (!ft_strcmp(tokens->next->content, "|"))
			{
				ft_printf("syntax error near unexpected token '|'\n");
				context->exit_status = 2;
				return (0);
			}
		}
		if (is_redirect(tokens->content))
		{
			if (!tokens->next)
			{
				ft_printf("syntax error near unexpected token  'newlinw'\n");
				context->exit_status = 2;
				return (0);
			}
			if (is_redirect(tokens->next->content) \
				|| !ft_strcmp(tokens->next->content, "|"))
			{
				ft_printf("syntax error near unexpected token '%s'", \
					tokens->content);
				context->exit_status = 2;
				return (0);
			}
		}		
		tokens = tokens->next;
	}
	return (1);
}
