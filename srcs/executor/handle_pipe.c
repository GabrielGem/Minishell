/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:34:18 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/01/22 19:28:42 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	pipe_recursive(t_ast_node *leaf, int input_fd, int output_fd, \
	t_data *context);

int	handle_pipe(t_ast_node *leaf, t_data *context)
{
	pipe_recursive(leaf, STDIN_FILENO, STDOUT_FILENO, context);
	return (0);
}

static int	pipe_recursive(t_ast_node *leaf, int input_fd, int output_fd, \
	t_data *context)
{
	int		pipefd[2];

	if (leaf->type.base == NODE_PIPE)
	{
		int	stdout_backup = dup(output_fd);
		pipe(pipefd);
		pipe_recursive((t_ast_node *)leaf->left, input_fd, pipefd[1], context);
		close(pipefd[1]);
		dup2(stdout_backup, STDOUT_FILENO);
		close(stdout_backup);
		pipe_recursive((t_ast_node *)leaf->right, pipefd[0], output_fd, context);
		close(pipefd[0]);
		if (input_fd != STDIN_FILENO)
			close(input_fd);
		if (output_fd != STDOUT_FILENO)
			close(output_fd);
	}
	else if (leaf->type.base == NODE_COMMAND)
	{
		if (input_fd != STDIN_FILENO)
		{
			dup2(input_fd, STDIN_FILENO);
			close(input_fd);
		}
		if (output_fd != STDOUT_FILENO)
		{
			dup2(output_fd, STDOUT_FILENO);
			close(output_fd);
		}
		executor(leaf, context);
	}
	return (0);
}
