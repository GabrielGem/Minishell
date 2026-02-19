/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 11:49:45 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/19 17:53:14 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_heredoc(char *delimiter, int fd, int len, int *lines);

int	heredoc(char *delimiter, char *temp_file, int count)
{
	int	fd;
	int	len;
	int	lines;

	fd = open(temp_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	len = ft_strlen(delimiter);
	lines = 0;
	if (process_heredoc(delimiter, fd, len, &lines))
	{
		printf("\nminishell: warning: here-document at line %d ", count);
		printf("delimited by end-of-file (wanted `%s')\n", delimiter);
	}
	close(fd);
	return (lines);
}

static int	process_heredoc(char *delimiter, int fd, int len, int *lines)
{
	char	*line;

	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(0);
		if (!line)
			return (1);
		if (ft_strncmp(line, delimiter, len) == 0 && line[len] == '\n')
		{
			free(line);
			return (0);
		}
		// if must expand
		ft_putstr_fd(line, fd);
		free(line);
		(*lines)++;
	}
	return (0);
}
