/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 20:20:54 by mmaquine          #+#    #+#             */
/*   Updated: 2026/02/21 16:00:27 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*parse_command(t_list **tokens, t_data *context)
{
	t_command	*cmd;
	t_list		*args_list;
	t_list		*current;
	t_redir		*redir;

	cmd = ft_calloc(1, sizeof(t_command));
	cmd->type.base = NODE_COMMAND;
	args_list = NULL;
	cmd->redirects = NULL;
	current = *tokens;
	while (current && ft_strcmp("|", current->content))
	{
		if (is_redirect(current->content))
		{
			redir = ft_calloc(1, sizeof(t_redir));
			redir->type = get_redirect_type(current->content);
			current = current->next;
			if (is_quote_token(current, '\'') || is_quote_token(current, '\"'))
				redir->expand = 0;
			else
				redir->expand = 1;
			//remover aspas tanto duplas ou simples.
			if (!current || !ft_strcmp("|", current->content) 
				|| is_redirect(current->content))
			{
				ft_printf("minishell: syntax error near unexpected %s\n", \
					current->content);
				free(redir);
				context->exit_status = 2;
				ft_lstclear(&cmd->redirects, free);
				free(cmd);
				return (NULL);
			}
			redir->filename = ft_strdup(current->content);
			ft_lstadd_back(&cmd->redirects, ft_lstnew(redir));
			current = current->next;
		}
		else
		{
			ft_lstadd_back(&args_list, ft_lstnew(ft_strdup(current->content)));
			current = current->next;
		}
	}
	cmd->args = list_to_array(args_list);
	cmd->is_builtin = is_builtin(cmd->args[0]);
	*tokens = current;
	ft_lstclear(&args_list, free);
	return (cmd);
}
