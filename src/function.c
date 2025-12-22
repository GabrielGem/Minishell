/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 14:38:08 by mmaquine          #+#    #+#             */
/*   Updated: 2025/12/22 18:47:04 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") ||
		ft_strcmp(cmd, "cd") ||
		ft_strcmp(cmd, "pwd") ||
		ft_strcmp(cmd, "export") ||
		ft_strcmp(cmd, "unset") ||
		ft_strcmp(cmd, "env") ||
		ft_strcmp(cmd, "exit"))
		return (1);
		
	return (0);
}

/*
When finding a | insert a ' ' before and after
*/
char	*find_pipe(char *cmd)
{
	char	*new_cmd;
	char	*sub_str;
	char	*pipe;

	pipe = ft_strchr(cmd, '|');
	if (!pipe)
		return (cmd);
	if (!*(pipe - 1) == ' ')
	{
		sub_str = ft_substr(cmd, 0, ft_strlen(pipe));
		new_cmd = ft_strjoin(sub_str, " ");
		free(sub_str);
	}
	sub_str = ft_strjoin(new_cmd, "!");
	free(new_cmd);
	if (!*(pipe + 1) == ' ')
		new_cmd = ft_strjoin(sub_str, " ");
	free(sub_str);
	
}
