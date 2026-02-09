/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 21:22:38 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/09 09:57:32 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tests.h"

int	handle_command_fd(t_ast_node *leaf, int input_fd, int output_fd, \
	t_data *context);
int	exec_builtin(t_data *context, char **args, int nb_builtin);
int	exec_command(t_data *context, char **args);
static void	setup_pipe(int input_fd, int output_fd);
static void setup_fd(int new_fd, int old_fd);
void	restore_fd(t_data *context);

int	handle_command(t_ast_node *leaf, t_data *context)
{
	int			status;
	t_command	*cmd;
	pid_t		pid;

	cmd = (t_command *)leaf;
	if (cmd->is_builtin)
		status = handle_command_fd(leaf, STDIN_FILENO, STDOUT_FILENO, context);
	else
	{
		pid = fork();
		if (pid == 0)
			status = handle_command_fd(leaf, STDIN_FILENO, STDOUT_FILENO, context);
		ft_lstadd_back(&context->pids, ft_lstnew((void *)(long)pid));
	}
	if (context->pids != NULL)
		status = wait_processes(context->pids);
	return (status);
}

int	handle_command_fd(t_ast_node *leaf, int input_fd, int output_fd, \
	t_data *context)
{
	int			status;
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
		if (redirect_file[0] == 1 || redirect_file[1] == 1)
			exit(1);
		free(redirect_file);
	}
	status = 0;
	if (cmd->is_builtin)
		status = exec_builtin(context, cmd->args, cmd->is_builtin);
	else
		status = exec_command(context, cmd->args);
	restore_fd(context);
	return (status);
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
	int					status;
	t_builtin			ft;
	static t_builtin	map[COUNT] = {
		//&b_echo,
		//&b_cd,
		//&b_pwd,
		NULL,
		NULL,
		NULL,
		NULL,
		&b_export,
		//&b_unset,
		//&b_env,
		//&b_exit
	};

	ft = map[nb_builtin];
	status = ft(context, args);
	return (status);
}

int	exec_command(t_data *context, char **args)
{
	char	**path;
	char	*command_path;
	char	**envp;

	command_path = args[0];
	if (!ft_strchr(args[0], '/'))
	{
		path = ft_split(hash_search(context->env, "PATH", ENV), ':');
		command_path = binary_search(path, args[0]);
	}
	if (!command_path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_context(context);
		exit(127);
	}
	envp = table_to_envp(context->env);
	execve(command_path, &args[1], envp);
	ft_putstr_fd("minishell: ", 2);
	perror(args[0]);
	free_context(context);
	exit(127);
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
