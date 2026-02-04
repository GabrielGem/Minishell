/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_context.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 20:14:17 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/04 13:59:22 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	close_fd(void *fd);
void	close_pid(void *pid);

void	free_context(t_data *context)
{
	destroy_table(context->env);
	//ft_free_split(context->envp);
	free_tree(context->root);
	ft_lstclear(&context->fds, close_fd);
	ft_lstclear(&context->pids, close_pid);
	close(context->stdin_backup);
	close(context->stdout_backup);
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
