/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 11:49:45 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/10 11:49:46 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_heredoc(char *delimiter, t_data *context)
{
	char	*line;
	int		fd;
	int		len;

	fd = open("/tmp/.heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	len = ft_strlen(delimiter);
	while (1)
	{
		ft_putstr_fd("> ", context->stdout_backup);
		line = get_next_line(context->stdin_backup);
		if (!line)
			break ;
		if (ft_strncmp(line, delimiter, len) == 0 && line[len] == '\n')
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		free(line);
	}
	close(fd);
	fd = open("/tmp/.heredoc_tmp", O_RDONLY);
	unlink("/tmp/.heredoc_tmp");
	return (fd);
}