/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 17:51:35 by mmaquine          #+#    #+#             */
/*   Updated: 2026/02/24 23:36:17 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	print_message1(t_data *context)
{
	ft_putstr_fd("syntax error near unexpected token 'newline'\n", 2);
	context->exit_status = 2;
	return (0);
}

static char	print_message2(t_data *context)
{
	ft_putstr_fd("syntax error near unexpected token '|'\n", 2);
	context->exit_status = 2;
	return (0);
}

static char	print_message3(t_data *context, char *str)
{
	char	*message;

	message = NULL;
	str_append(&message, "syntax error near unexpected token '");
	str_append(&message, str);
	str_append(&message, "'\n");
	ft_putstr_fd(message, 2);
	free(message);
	context->exit_status = 2;
	return (0);
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
		return (print_message2(context));
	while (tokens)
	{
		if (!ft_strcmp(tokens->content, "|"))
		{
			if (!tokens->next)
				return (print_message1(context));
			if (!ft_strcmp(tokens->next->content, "|"))
				return (print_message2(context));
		}
		if (is_redirect(tokens->content))
		{
			if (!tokens->next)
				return (print_message1(context));
			if (is_redirect(tokens->next->content)
				|| !ft_strcmp(tokens->next->content, "|"))
				return (print_message3(context, tokens->next->content));
		}
		tokens = tokens->next;
	}
	return (1);
}
