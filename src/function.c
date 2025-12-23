/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 14:38:08 by mmaquine          #+#    #+#             */
/*   Updated: 2025/12/23 15:39:11 by mmaquine         ###   ########.fr       */
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
	char	*pipe_ch;

	pipe_ch = ft_strnstr(cmd, "|", ft_strlen(cmd));
	if (!pipe_ch)
		return (cmd);
	while (pipe_ch)
	{
		if (pipe_ch != cmd && *(pipe_ch - 1) != ' ')
		{	
			sub_str = ft_substr(cmd, 0, pipe_ch - new_cmd);
			str_append(&sub_str, " |");
			str_append(&sub_str, pipe_ch + 1);
		}
		if (*(pipe_ch + 1) != '\0' && *(pipe_ch + 1) != ' ')
		{
			new_cmd = ft_substr(new_cmd, 0, pipe_ch - new_cmd + 1);
			str_append(&sub_str, " ");
			str_append(&sub_str, pipe_ch + 1);
			new_cmd = sub_str;
		}
		pipe_ch = ft_strchr(new_cmd, '|');
		pipe_ch = ft_strchr(pipe_ch + 1, '|');

	}
	free(cmd);
	return (new_cmd);
}

char	*find_pipe2(char *cmd)
{
	
}
