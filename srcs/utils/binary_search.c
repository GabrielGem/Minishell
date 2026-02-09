/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_search.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 10:09:42 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/07 15:48:27 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*binary_search(char **path, char *cmd)
{
	char	*path_binary;
	char	*temp;

	while (*path)
	{
		temp = ft_strjoin(*path, "/");
		path_binary = ft_strjoin(temp, cmd);
		free(temp);
		if (is_valid_executable(path_binary))
			return (path_binary);
		free(path_binary);
		path++;
	}
	return (NULL);
}
