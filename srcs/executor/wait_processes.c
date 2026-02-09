/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 15:55:05 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/07 16:40:57 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_processes(t_list *pids)
{
	int		status;
	int		last_status;
	t_list	*current;

	current = pids;
	status = 0;
	last_status = 0;
	while (current)
	{
		waitpid((pid_t)(long)current->content, &status, 0);
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		current = current->next;
	}
	return (last_status);
}
