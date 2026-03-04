/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 20:14:17 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/03/04 10:41:40 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_shell(t_data *context)
{
	destroy_table(context->env);
	context->env = NULL;
	free_tree(context->root);
	context->root = NULL;
	ft_lstclear(&context->fds, close_fd);
	ft_lstclear(&context->pids, close_pid);
	close(context->stdin_backup);
	close(context->stdout_backup);
	free(context);
}

void	close_fd(void *fd)
{
	close((int)(long)fd);
}

void	close_pid(void *pid)
{
	(void)pid;
	return ;
}
