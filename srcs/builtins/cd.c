/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 15:05:55 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/18 17:42:41 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_work_directory(t_data *context, char *new_dir);
static char	*get_target(t_data *context, char **args, char **error_msg);

int	b_cd(t_data *context, char **args)
{
	char	*target_dir;
	char	*error_msg;

	if (args[1] && args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDOUT_FILENO);
		return (1);
	}
	target_dir = get_target(context, args, &error_msg);
	if (!target_dir)
	{
		ft_putendl_fd(error_msg, 2);
		return (1);
	}
	if (update_work_directory(context, target_dir))
		return (1);
	return (0);
}

static char	*get_target(t_data *context, char **args, char **error_msg)
{
	char	*dir;

	if (!args[1])
	{
		dir = hash_search(context->env, "HOME", ENV);
		*error_msg = "minishell: cd: HOME not set\n";
	}
	else if (!ft_strncmp(args[1], "~", 2))
	{
		dir = hash_search(context->env, "HOME2", SET);
		*error_msg = "minishell: cd: HOME not set\n";
	}
	else if (!ft_strncmp(args[1], "-", 2))
	{
		dir = hash_search(context->env, "OLDPWD", ENV);
		if (dir)
			ft_putendl_fd(dir, STDOUT_FILENO);
		*error_msg = "minishell: cd: OLDPWD not set\n";
	}
	else
		return (args[1]);
	return (dir);
}

static int	update_work_directory(t_data *context, char *new_dir)
{
	char	*old_dir;

	old_dir = getcwd(NULL, 0);
	if (chdir(new_dir) == -1)
	{
		ft_putstr_fd("minishell: cd", 2);
		perror(new_dir);
		free(old_dir);
		return (1);
	}
	new_dir = getcwd(NULL, 0);
	hash_upsert(context->env, "PWD", new_dir, ENV);
	hash_upsert(context->env, "OLDPWD", old_dir, ENV);
	free(new_dir);
	free(old_dir);
	return (0);
}
