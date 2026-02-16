/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command_heredoc.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 16:43:27 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/16 18:24:39 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*generate_unique_name(void);

int	handle_command_heredoc(t_ast_node *leaf, t_data *context)
{
	t_command	*cmd;
	t_list	*list;
	t_redir	*redir;
	char	*name;

	(void)context;
	cmd = (t_command *)leaf;
	list = cmd->redirects;
	while (list)
	{
		redir = (t_redir *)list->content;
		if (redir->type == HEREDOC)
		{
			name = generate_unique_name();
			process_heredoc(redir->filename, name);
			free(redir->filename);
			redir->filename = name;
		}
		list = list->next;
	}
	return (0);
}

static char	*generate_unique_name(void)
{
	static int	i;
	char		*num;
	char		*address;
	char		*name;
	char		*temp;

	num = ft_itoa(i++);
	address = ft_uitoa_base((unsigned long int)num, "0123456789abcdef");
	temp = ft_strjoin("/tmp/.heredoc_temp_", address);
	name = ft_strjoin(temp, num);
	free(temp);
	return (name);
}
