/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 11:11:26 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/01/08 10:52:13 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redirs(t_list *lst)
{
	char	*filename;
	int		fd;
	int		last_fd;

	last_fd = -1;
	while (lst)
	{
		filename = ((t_redir *)lst->content)->filename;
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(filename);
			if (last_fd != -1)
				close(last_fd);
			return (-1);
		}
		if (last_fd != -1)
			close(last_fd);
		last_fd = fd;
		lst = lst->next;
	}
	return (last_fd);
}
