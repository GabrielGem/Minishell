/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 11:49:45 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/16 18:31:02 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_heredoc(char *delimiter, char *temp_file)
{
	char	*line;
	int		fd;
	int		len;

	fd = open(temp_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	len = ft_strlen(delimiter);
	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(0);
		if (!line)
			break ;
		if (ft_strncmp(line, delimiter, len) == 0 && line[len] == '\n')
		{
			free(line);
			break ;
		}
		// if must expand
		ft_putstr_fd(line, fd);
		free(line);
	}
	close(fd);
}
