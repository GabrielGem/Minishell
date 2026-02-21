/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 11:49:45 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/21 17:48:59 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_heredoc(t_redir *redir, int fd, int *lines, t_data *context);

int	heredoc(char *temp_file, t_redir *redir, t_data *context)
{
	int	fd;
	int	lines;

	fd = open(temp_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	lines = 0;
	if (process_heredoc(redir, fd, &lines, context))
	{
		printf("\nminishell: warning: here-document at line %d ", context->count_line);
		printf("delimited by end-of-file (wanted `%s')\n", redir->filename);
	}
	close(fd);
	return (lines);
}

static int	process_heredoc(t_redir *redir, int fd, int *lines, t_data *context)
{
	char	*line;
	int		len;

	len = ft_strlen(redir->filename);
	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(0);
		if (!line)
			return (1);
		if (ft_strncmp(line, redir->filename, len) == 0 && line[len] == '\n')
		{
			free(line);
			return (0);
		}
		if (redir->expand)
			line = expand_all_vars(line, context);
		ft_putstr_fd(line, fd);
		free(line);
		(*lines)++;
	}
	return (0);
}
