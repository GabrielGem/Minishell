/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 21:22:38 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/01/15 13:54:41 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_process(char **args, char **envp);

int	handle_command(t_ast_node *leaf, t_data *context)
{
	t_command	*cmd;
	pid_t		id;
	int			status;

	cmd = (t_command *)leaf;
	status = 0;
	id = fork();
	if (id == -1)
		return (-1);
	if (id == 0)
		child_process(cmd->args, context->envp);
	waitpid(id, &status, 0);
	return (status);
}

static void	child_process(char **args, char **envp)
{
	execve(args[0], &args[1], envp);
}
