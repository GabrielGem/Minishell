/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:34:18 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/04 14:36:01 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	pipe_recursive(t_ast_node *leaf, int input_fd, int output_fd, \
	t_data *context);

int	handle_pipe(t_ast_node *leaf, t_data *context)
{
	int	last_status;

	pipe_recursive(leaf, STDIN_FILENO, STDOUT_FILENO, context);
	last_status = wait_processes(context->pids);
	return (last_status);
}

static int	pipe_recursive(t_ast_node *leaf, int input_fd, int output_fd, \
	t_data *context)
{
	int		pipefd[2];
	int		status;
	pid_t	left;
	pid_t	right;

	status = 0;
	if (leaf->type.base == NODE_COMMAND)
		return (handle_command_fd(leaf, input_fd, output_fd, context));
	if (leaf->type.base == NODE_PIPE)
	{
		pipe(pipefd);
		ft_lstadd_back(&context->fds, ft_lstnew((void *)(long)pipefd[0]));
		ft_lstadd_back(&context->fds, ft_lstnew((void *)(long)pipefd[1]));
		left = fork();
		if (left == 0)
		{
			close(pipefd[0]);
			pipe_recursive((t_ast_node *)leaf->left, input_fd, pipefd[1], context);
			exit(0);
		}
		right = fork();
		if (right == 0)
		{
			close(pipefd[1]);
			status = pipe_recursive((t_ast_node *)leaf->right, pipefd[0], \
			output_fd, context);
			exit(status);
		}
		ft_lstadd_back(&context->pids, ft_lstnew((void *)(long)left));
		ft_lstadd_back(&context->pids, ft_lstnew((void *)(long)right));
	}
	//ft_lstclear(&context->fds, close_fd);
	return (status);
}
