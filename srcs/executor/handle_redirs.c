/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 11:11:26 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/01/13 16:07:47 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_file(char *file, int direction);
static int	*handle_error(int *fds, char *file);
static void	close_fds(int *fds);
static void	update_fds(int *fds, int fd, int type);

int	*handle_redirs(t_list *lst)
{
	t_redir	*redir;
	int		fd;
	int		*fds;

	fds = ft_calloc(sizeof(int), 2);
	fds[0] = -1;
	fds[1] = -1;
	while (lst)
	{
		redir = (t_redir *)lst->content;
		fd = open_file(redir->filename, redir->type);
		if (fd == -1)
			return (handle_error(fds, redir->filename));
		update_fds(fds, fd, redir->type);
		lst = lst->next;
	}
	return (fds);
}

static int	open_file(char *file, int direction)
{
	int		flags;
	mode_t	mode;

	mode = 0644;
	if (direction == REDIN)
		flags = O_RDONLY;
	else if (direction == REDOUT)
		flags = O_CREAT | O_WRONLY | O_TRUNC;
	else
		flags = O_CREAT | O_WRONLY | O_APPEND;
	return (open(file, flags, mode));
}

static void	update_fds(int *fds, int fd, int type)
{
	if (type == REDIN)
	{
		if (fds[0] != -1)
			close(fds[0]);
		fds[0] = fd;
	}
	else
	{
		if (fds[1] != -1)
			close(fds[1]);
		fds[1] = fd;
	}
}

static int	*handle_error(int *fds, char *file)
{
	ft_putstr_fd("minishell: ", 2);
	perror(file);
	close_fds(fds);
	fds[0] = 1;
	fds[1] = 1;
	return (fds);
}

static void	close_fds(int *fds)
{
	if (fds[0] != -1)
		close(fds[0]);
	if (fds[1] != -1)
		close(fds[1]);
}
