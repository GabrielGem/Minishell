/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 15:55:05 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/01/27 15:59:21 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_processes(t_list *pids)
{
	int		status;
	pid_t	pid;
	t_list	*current;

	current = pids;
	status = 0;
	while (current)
	{
		pid = (long)current->content;
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		current = current->next;
	}
	return (status);
}
