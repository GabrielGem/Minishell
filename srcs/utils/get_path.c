/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 15:45:17 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/19 15:45:37 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(char *cmd, t_data *context)
{
	char	*command_path;
	char	**path;

	if (ft_strchr(cmd, '/'))
		command_path = cmd;
	else
	{
		path = ft_split(hash_search(context->env, "PATH", ENV), ':');
		command_path = binary_search(path, cmd);
		ft_free_split(path);
	}
	return (command_path);
}
