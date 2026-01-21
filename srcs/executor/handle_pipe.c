/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:34:18 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/01/21 16:59:25 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	handle_pipe(t_ast_node *leaf, t_data *context)
{
	t_exec	*pipe_context;
	int		*pipefd;

	if (leaf->type.base == NODE_COMMAND)
		handle_command(leaf, context);
	pipefd = NULL;
	if (pipe(pipefd))
		return (1);
	pipe_context = ft_calloc(1, sizeof(t_exec));
	pipe_context->stdin_backup = dup(STDIN_FILENO);
	pipe_context->stdout_backup = dup(STDOUT_FILENO);
	if (fork() == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		handle_pipe((t_ast_node *)leaf->left, context);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		dup2(pipe_context->stdout_backup, STDOUT_FILENO);
		handle_pipe((t_ast_node *)leaf->right, context);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	return (0);
}
