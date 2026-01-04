/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_search.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 10:09:42 by gabrgarc          #+#    #+#             */
/*   Updated: 2025/12/23 17:24:39 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*binary_search(char **path, char *cmd)
{
	char	*path_binary;

	while (*path)
	{
		path_binary = ft_strjoin(*path, cmd);
		if (is_valid_executable(path_binary))
			return (path_binary);
		free(path_binary);
		path++;
	}
	return (NULL);
}
