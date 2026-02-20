/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 15:55:05 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/20 17:58:59 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_processes(t_list *pids)
{
	int		status;
	int		last_status;
	t_list	*current;
	pid_t	last_pid;

	if (pids == NULL)
		return (0);
	current = pids;
	last_pid = (pid_t)(long)ft_lstlast(current)->content;
	status = 0;
	last_status = 0;
	while (current)
	{
		if (waitpid((pid_t)(long)current->content, &status, 0) == last_pid)
		{
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_status = 128 + WTERMSIG(status);
		}
		current = current->next;
	}
	return (last_status);
}
