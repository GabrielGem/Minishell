/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 20:20:54 by mmaquine          #+#    #+#             */
/*   Updated: 2026/02/11 20:32:06 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*parse_command(t_list **tokens)
{
	t_command	*cmd;
	t_list		*args_list;
	t_list		*current;

	cmd = ft_calloc(1, sizeof(t_command));
	cmd->type.base = NODE_COMMAND;
	args_list = NULL;
	cmd->redirects = NULL;
	current = *tokens;
	while (current && !ft_strcmp("|", current->content))
	{
		if (is_redirect(current->content))
		{
			;	
		}
		else
		{
			ft_lstadd_back(&args_list, ft_lstnew(current->content));
			current = current->next;
		}
	}
	cmd->args = list_to_array(args_list);
	//verificar builtins
	*tokens = current;
	return (cmd)
}
