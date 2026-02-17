/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 11:49:45 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/17 11:48:14 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_heredoc(char *delimiter, char *temp_file, int count)
{
	char	*line;
	int		lines;
	int		fd;
	int		len;

	lines = 0;
	fd = open(temp_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	len = ft_strlen(delimiter);
	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(0);
		if (!line)
		{
			printf("\nminishell: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n", count, delimiter);
			break ;
		}
		if (ft_strncmp(line, delimiter, len) == 0 && line[len] == '\n')
		{
			free(line);
			break ;
		}
		lines++;
		// if must expand
		ft_putstr_fd(line, fd);
		free(line);
	}
	close(fd);
	return (lines);
}
