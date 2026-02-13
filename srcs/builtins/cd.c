/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 15:05:55 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/11 18:50:19 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_work_directory(t_data *data, char *new_dir);

int	b_cd(t_data *context, char **args)
{
	char	*target_dir;

	if (args[2] != NULL)
	{
		ft_putstr_fd("minishell: cd: too many argunts\n", STDOUT_FILENO);
		return (1);
	}
	if (!args[1] || !ft_strncmp(args[1], "~", 2))
		target_dir = hash_search(context->env, "HOME", ENV);
	else if (!ft_strncmp(args[1], "-", 2))
	{
		target_dir = hash_search(context->env, "OLDPWD", ENV);
		ft_putendl_fd(target_dir, STDOUT_FILENO);
	}
	else
		target_dir = args[1];
	if (update_work_directory(context, target_dir))
		return (1);
	return (0);
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
