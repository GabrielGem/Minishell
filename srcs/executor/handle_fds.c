/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 18:36:22 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/11 18:37:27 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_fd(t_data *context)
{
	if (STDIN_FILENO != context->stdin_backup)
		dup2(context->stdin_backup, STDIN_FILENO);
	if (STDOUT_FILENO != context->stdout_backup)
		dup2(context->stdout_backup, STDOUT_FILENO);
}

void	setup_pipe(int input_fd, int output_fd)
{
	setup_fd(input_fd, STDIN_FILENO);
	setup_fd(output_fd, STDOUT_FILENO);
}

void	setup_fd(int new_fd, int old_fd)
{
	if (new_fd != old_fd)
	{
		dup2(new_fd, old_fd);
		close(new_fd);
	}
}
