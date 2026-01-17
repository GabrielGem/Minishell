/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 21:22:38 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/01/16 21:53:49 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	setup_child_io(int input_fd, int output_fd);
static void	child_process(char **args, char **envp);

int	handle_command(t_ast_node *leaf, t_data *context)
{
	t_command	*cmd;
	pid_t		id;
	int			status;
	int			*fd;

	cmd = (t_command *)leaf;
	status = 0;
	id = fork();
	if (id == -1)
		return (-1);
	if (id == 0)
	{
		fd = NULL;
		if (cmd->redirects)
			fd = handle_redirs(cmd->redirects);
		//if (fd[0] == -1)
		//	fd[0] = dup(STDIN_FILENO);
		//if (fd[1] == -1)
		//	fd[1] = dup(STDOUT_FILENO);
		setup_child_io(fd[0], fd[1]);
		close(fd[0]);
		close(fd[1]);
		child_process(cmd->args, context->envp);
	}
	waitpid(id, &status, 0);
	return (status);
}

static void	setup_child_io(int input_fd, int output_fd)
{
	if (dup2(input_fd, STDIN_FILENO) == -1
		|| dup2(output_fd, STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("Error: Failed to redirect I/O\n", 2);
	}
}

static void	child_process(char **args, char **envp)
{
	execve(args[0], &args[1], envp);
}
