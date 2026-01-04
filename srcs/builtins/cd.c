/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 15:05:55 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/01/03 22:39:43 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_work_directory(t_data *data, char *new_dir);

void	cd(t_data *data, t_command *cmd)
{
	char	*pwd;
	char	*target_dir;

	if (cmd->args[1] && cmd->args[2])
		// error message "minishell: cd: too many arguments" and exit
	if (!cmd->args[1] || !ft_strncmp(cmd->args[1], "~"))
		target_dir = hash_search(data->env, "HOME");
	else if (!ft_strncmp(cmd->args[1], "-"))
	{
		target_dir = hash_search(data->env, "OLDPWD");
		pwd = getcwd(NULL, 0);
		ft_putstr_fd(pwd, 1); // change to putendl?
		free(pwd);
	}
	else
		target_dir = cmd->args[1];
	if (update_work_directory(data, target_dir));
		return (1);
	return (0);
}

static int	update_work_directory(t_data *data, char *new_dir)
{
	char	*old_dir;

	old_dir = getcwd(NULL, 0);
	if (chdir(new_dir) == -1)
	{
		ft_putstr_fd("minishell: cd");
		perror(new_dir);
		free(old_dir);
		return (1);
	}
	new_dir = getcwd(NULL, 0);
	hash_upsert(data->env, "PWD", new_dir);
	hash_upsert(data->env, "OLDPWD", old_dir);
	free(new_dir);
	free(old_dir);
	return (0);
}
