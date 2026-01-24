/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 21:22:38 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/01/23 20:40:43 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_command_fd(t_ast_node *leaf, int input_fd, int output_fd, \
	t_data *context);

int	handle_command(t_ast_node *leaf, t_data *context)
{
	return (handle_command_fd(leaf, STDIN_FILENO, STDOUT_FILENO, context));
}

int	handle_command_fd(t_ast_node *leaf, int input_fd, int output_fd, t_data *context)
{
	t_command	*cmd;
	pid_t		id;
	int			status;
	int			*redirs;

	cmd = (t_command *)leaf;
	id = fork();
	if (id == -1)
		return (-1);
	if (id == 0)
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
		if (cmd->redirects != NULL)
		{
			redirs = handle_redirs(cmd->redirects);
			if (redirs[REDIN] == 1 || redirs[REDOUT] == 1)
			{
				free_context(context);
				exit(1);
			}
			if (redirs[REDIN] != -1)
				dup2(redirs[REDIN], STDIN_FILENO);
			if (redirs[REDOUT] != -1)
				dup2(redirs[REDOUT], STDOUT_FILENO);
			close(redirs[REDIN]);
			close(redirs[REDOUT]);
		}
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
