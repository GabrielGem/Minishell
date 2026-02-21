/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:34:18 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/21 11:45:50 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	pipe_recursive(t_ast_node *leaf, int input_fd, int output_fd,\
	t_data *context);
void		close_pid(void *pid);
static int	left_branch(t_ast_node *leaf, int input_fd, int *pipefd,\
	t_data *context);
static int	right_branch(t_ast_node *leaf, int output_fd, int *pipefd,\
	t_data *context);

int	handle_pipe(t_ast_node *leaf, t_data *context)
{
	int	last_status;

	pipe_recursive(leaf, STDIN_FILENO, STDOUT_FILENO, context);
	last_status = wait_processes(context->pids);
	return (last_status);
}

static int	pipe_recursive(t_ast_node *leaf, int input_fd, int output_fd,\
	t_data *context)
{
	int		pipefd[2];
	int		status;

	status = 0;
	if (leaf->type.base == NODE_COMMAND)
		return (handle_command_fd(leaf, input_fd, output_fd, context));
	if (leaf->type.base == NODE_PIPE)
	{
		pipe(pipefd);
		ft_lstadd_back(&context->fds, ft_lstnew((void *)(long)pipefd[0]));
		ft_lstadd_back(&context->fds, ft_lstnew((void *)(long)pipefd[1]));
		left_branch(leaf, input_fd, pipefd, context);
		right_branch(leaf, output_fd, pipefd, context);
		close(pipefd[1]);
		close(pipefd[0]);
	}
	return (status);
}

static int	left_branch(t_ast_node *leaf, int input_fd, int *pipefd,\
	t_data *context)
{
	pid_t	pid_left;
	int		status;

	status = 0;
	pid_left = fork();
	if (pid_left == 0)
	{
		setup_signals_exec();
		close(pipefd[0]);
		status = pipe_recursive((t_ast_node *)leaf->left, input_fd, pipefd[1], \
context);
		close(pipefd[1]);
		free_shell(context);
		exit(status);
	}
	ft_lstadd_back(&context->pids, ft_lstnew((void *)(long)pid_left));
	return (status);
}

static int	right_branch(t_ast_node *leaf, int output_fd, int *pipefd,\
	t_data *context)
{
	pid_t	pid_right;
	int		status;

	status = 0;
	pid_right = fork();
	if (pid_right == 0)
	{
		setup_signals_exec();
		close(pipefd[1]);
		pipe_recursive((t_ast_node *)leaf->right, pipefd[0], output_fd, \
context);
		close(pipefd[0]);
		status = wait_processes(context->pids);
		free_shell(context);
		exit(status);
	}
	ft_lstadd_back(&context->pids, ft_lstnew((void *)(long)pid_right));
	return (status);
}
