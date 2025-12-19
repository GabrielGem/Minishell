/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*  check_commands.c                                     :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*  By: gabrgarc <gabrgarc@student.42sp.org.br>      +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*  Created: 2025/12/19 17:20:35 by gabrgarc            #+#    #+#            */
/*  Updated: 2025/12/19 17:20:41 by gabrgarc           ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

static int	validate_cmd(t_info *info, char **cmd, char **path_cmd, int flag);
static char	*find_command_in_path(t_info *info, char *cmd);
static int	is_valid_executable(char *path);

void	check_commands(t_info *info)
{
	if (!validate_cmd(info, info->cmd1, &info->path_cmd1, relative)
		|| !validate_cmd(info, info->cmd2, &info->path_cmd2, relative2))
	{
		clear_memory(info);
		exit(127);
	}
}

static int	validate_cmd(t_info *info, char **cmd, char **path_cmd, int flag)
{
	if (ft_strchr(cmd[0], '/'))
	{
		*path_cmd = cmd[0];
		if (!is_valid_executable(*path_cmd))
		{
			ft_putstr_fd("pipex: ", 2);
			ft_putstr_fd(cmd[0], 2);
			perror(":\b");
			return (0);
		}
	}
	else
	{
		info->flags |= flag;
		*path_cmd = find_command_in_path(info, cmd[0]);
		if (*path_cmd == NULL)
		{
			ft_putstr_fd("pipex: ", 2);
			ft_putstr_fd(cmd[0], 2);
			perror(":\b");
			return (0);
		}
	}
	return (1);
}

static char	*find_command_in_path(t_info *info, char *cmd)
{
	int		i;
	char	*full_path;

	i = 0;
	while (info->path[i])
	{
		full_path = ft_strjoin(info->path[i], cmd);
		if (is_valid_executable(full_path))
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

static int	is_valid_executable(char *path)
{
	return (access(path, F_OK) == 0 && access(path, X_OK) == 0);
}
