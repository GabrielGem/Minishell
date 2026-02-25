/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 10:26:49 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/19 15:46:29 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	file_exist(char *path)
{
	return (access(path, F_OK) == 0);
}

int	is_executable(char *path)
{
	return (access(path, X_OK) == 0);
}

int	is_directory(char *path)
{
	struct stat	buffer;

	if (stat(path, &buffer) == 0 && S_ISDIR(buffer.st_mode) > 0)
		return (1);
	return (0);
}

int	exit_error(char *cmd, int code, t_data *context)
{
	if (code == 127)
	{
		if (!ft_strchr(cmd, '/'))
		{
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": command not found\n", 2);
		}
		else
		{
			ft_putstr_fd("minishell: ", 2);
			perror(cmd);
		}
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		if (is_directory(cmd))
			ft_putstr_fd(": Is a directory\n", 2);
		else
			ft_putstr_fd(": Permission denied\n", 2);
	}
	free_shell(context);
	exit(code);
}

int	valid_command(char *cmd)
{
	int		error_code;

	error_code = 0;
	if (!file_exist(cmd))
		error_code = 127;
	else if (is_directory(cmd))
		error_code = 126;
	else if (!is_executable(cmd))
		error_code = 126;
	return (error_code);
}
