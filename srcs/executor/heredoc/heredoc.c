/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 11:49:45 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/17 09:30:22 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_heredoc(char *delimiter, char *temp_file)
{
	static int	count;
	int			count_lines;
	char		*line;
	int			fd;
	int			len;

	count_lines = 0;
	fd = open(temp_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	len = ft_strlen(delimiter);
	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(0);
		if (!line)
		{
			count += 1;
			printf("\nminishell: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n", count, delimiter);
			break ;
		}
		if (ft_strncmp(line, delimiter, len) == 0 && line[len] == '\n')
		{
			free(line);
			break ;
		}
		count_lines++;
		// if must expand
		ft_putstr_fd(line, fd);
		free(line);
	}
	count += count_lines;
	close(fd);
}
