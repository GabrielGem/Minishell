/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_context.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 20:14:17 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/01/24 12:04:40 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	close_fd(void *fd);

void	free_context(t_data *context)
{
	destroy_table(context->env);
	//ft_free_split(context->envp);
	//context->envp = NULL;
	free_tree(context->root);
	ft_lstclear(&context->fds, close_fd);
}

void	close_fd(void *fd)
{
	close((int)(long)fd);
}
