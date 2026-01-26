/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 21:22:38 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/01/26 16:53:42 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			handle_command_fd(t_ast_node *leaf, int input_fd, int output_fd, \
	t_data *context);
static void	duplicate_fd(int new_fd, int old_fd);
static void	redirects(t_list *redirs, t_data *context);

int	handle_command(t_ast_node *leaf, t_data *context)
{
	return (handle_command_fd(leaf, STDIN_FILENO, STDOUT_FILENO, context));
}

int	handle_command_fd(t_ast_node *leaf, int input_fd, int output_fd, \
	t_data *context)
{
	t_command	*cmd;
	pid_t		id;
	int			status;

	cmd = (t_command *)leaf;
	id = fork();
	if (id == -1)
		return (-1);
	if (id == 0)
	{
		if (input_fd != STDIN_FILENO)
			duplicate_fd(input_fd, STDIN_FILENO);
		if (output_fd != STDOUT_FILENO)
			duplicate_fd(output_fd, STDOUT_FILENO);
		if (cmd->redirects != NULL)
			redirects(cmd->redirects, context);
		execve(cmd->args[0], &cmd->args[1], context->envp);
		ft_putstr_fd("minishell: ", 2);
		perror(cmd->args[0]);
		free_context(context);
		exit(127);
	}
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	if (output_fd != STDOUT_FILENO)
		close(output_fd);
	status = 0;
	waitpid(id, &status, 0);
	return (WEXITSTATUS(status));
}

static void	duplicate_fd(int new_fd, int old_fd)
{
	dup2(new_fd, old_fd);
	close(new_fd);
}

static void	redirects(t_list *redirs, t_data *context)
{
	int	*fds;

	fds = handle_redirs(redirs);
	if (fds[REDIN] == 1 || fds[REDOUT] == 1)
	{
		free_context(context);
		exit(1);
	}
	if (fds[REDIN] != -1)
		duplicate_fd(fds[REDIN], STDIN_FILENO);
	if (fds[REDOUT] != -1)
		duplicate_fd(fds[REDOUT], STDOUT_FILENO);
}
