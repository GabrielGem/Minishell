/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 21:22:38 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/14 18:39:12 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tests.h"

int			handle_command_fd(t_ast_node *leaf, int input_fd, int output_fd, \
	t_data *context);
static int	exec_builtin(t_data *context, char **args, int nb_builtin);
static int	exec_command(t_data *context, char **args);

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
			status = handle_command_fd(leaf, STDIN_FILENO, STDOUT_FILENO, \
				context);
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
		redirect_file = handle_redirs(cmd->redirects, context);
		if (redirect_file[0] != -1)
			setup_fd(redirect_file[0], STDIN_FILENO);
		if (redirect_file[1] != -1)
			setup_fd(redirect_file[1], STDOUT_FILENO);
		if (redirect_file[0] == 1 || redirect_file[1] == 1)
		{
			free(redirect_file);
			free_shell(context);
			exit(1);
		}
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

static int	exec_builtin(t_data *context, char **args, int nb_builtin)
{
	int					status;
	t_builtin			ft;
	static t_builtin	map[COUNT] = {
		[ECHO] = b_echo,
		[CD] = b_cd,
		[PWD] = b_pwd,
		[B_EXPORT] = b_export,
		[UNSET] = b_unset,
		[B_ENV] = b_env,
		[EXIT] = b_exit
	};

	ft = map[nb_builtin];
	status = ft(context, args);
	return (status);
}

static int	exec_command(t_data *context, char **args)
{
	char	*command_path;
	char	**envp;
	int		error_code;

	command_path = get_path(args[0], context);
	if (!command_path)
		exit_error(args[0], 127, context);
	error_code = valid_command(command_path);
	if (error_code != 0)
	{
		if (command_path != args[0])
			free(command_path);
		exit_error(args[0], error_code, context);
	}
	envp = table_to_envp(context->env);
	execve(command_path, args, envp);
	ft_putstr_fd("minishell: ", 2);
	ft_free_split(envp);
	perror(args[0]);
	free_shell(context);
	exit(127);
}
