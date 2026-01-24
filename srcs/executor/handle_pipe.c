/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:34:18 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/01/23 19:22:11 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	pipe_recursive(t_ast_node *leaf, int input_fd, int output_fd, \
	t_data *context);

int	handle_pipe(t_ast_node *leaf, t_data *context)
{
	context->fds = ft_lstnew((void *)(long)123456789);
	return (pipe_recursive(leaf, STDIN_FILENO, STDOUT_FILENO, context));
}

static int	pipe_recursive(t_ast_node *leaf, int input_fd, int output_fd, \
	t_data *context)
{
	int		pipefd[2];
	int		status;

	if (leaf->type.base == NODE_COMMAND)
		return (handle_command_fd(leaf, input_fd, output_fd, context));
	if (leaf->type.base == NODE_PIPE)
	{
		pipe(pipefd);
		ft_lstadd_back(&context->fds, ft_lstnew((void *)(long)pipefd[0]));
		ft_lstadd_back(&context->fds, ft_lstnew((void *)(long)pipefd[1]));
		pipe_recursive((t_ast_node *)leaf->left, input_fd, pipefd[1], context);
		status = pipe_recursive((t_ast_node *)leaf->right, pipefd[0], \
			output_fd, context);
	}
	return (status);
}
