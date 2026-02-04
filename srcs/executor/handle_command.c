/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 21:22:38 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/04 13:51:40 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_command_fd(t_ast_node *leaf, int input_fd, int output_fd, \
	t_data *context);
int	exec_builtin(t_data *context, char **args, int nb_builtin);
int	exec_command(t_data *context, char **args);
static void	setup_pipe(int input_fd, int output_fd);
static void setup_fd(int new_fd, int old_fd);
void	restore_fd(t_data *context);

int	handle_command(t_ast_node *leaf, t_data *context)
{
	int		status;

	handle_command_fd(leaf, STDIN_FILENO, STDOUT_FILENO, context);
	status = wait_processes(context->pids);
	return (status);
}

int	handle_command_fd(t_ast_node *leaf, int input_fd, int output_fd, \
	t_data *context)
{
	t_command	*cmd;
	int			*redirect_file;

	cmd = (t_command *)leaf;
	setup_pipe(input_fd, output_fd);
	if (cmd->redirects != NULL)
	{
		redirect_file = handle_redirs(cmd->redirects);
		if (redirect_file[0] != -1)
			setup_fd(redirect_file[0], STDIN_FILENO);
		if (redirect_file[1] != -1)
			setup_fd(redirect_file[1], STDOUT_FILENO);
	}
	if (cmd->is_builtin)
		exec_builtin(context, cmd->args, cmd->is_builtin);
	else
		exec_command(context, cmd->args);
	restore_fd(context);
	return (0); //TODO
}

void	restore_fd(t_data *context)
{
	if (STDIN_FILENO != context->stdin_backup)
		dup2(context->stdin_backup, STDIN_FILENO);
	if (STDOUT_FILENO != context->stdout_backup)
		dup2(context->stdout_backup, STDOUT_FILENO);
}

int	exec_builtin(t_data *context, char **args, int nb_builtin)
{
	t_builtin			ft;
	static t_builtin	map[COUNT] = {
		//&b_echo,
		NULL,
		NULL,
		NULL,
		NULL,
		//&b_cd,
		//&b_pwd,
		&b_export,
		//&b_unset,
		//&b_env,
		//&b_exit
	};

	ft = map[nb_builtin];
	ft(context, args);
	return (0); //TODO
}

int	exec_command(t_data *context, char **args)
{
	char	**envp;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		envp = table_to_envp(context->env);
		execve(args[0], &args[1], envp);
		ft_putstr_fd("minishell: ", 2);
		perror(args[0]);
		free_context(context);
		exit(127);
	}
	ft_lstadd_back(&context->pids, ft_lstnew((void *)(long)pid));
	return (0); //TODO
}

static void	setup_pipe(int input_fd, int output_fd)
{
	setup_fd(input_fd, STDIN_FILENO);
	setup_fd(output_fd, STDOUT_FILENO);
}

static void setup_fd(int new_fd, int old_fd)
{
	if (new_fd != old_fd)
	{
		dup2(new_fd, old_fd);
		close(new_fd);
	}
}
