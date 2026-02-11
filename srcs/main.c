/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 09:58:31 by mmaquine          #+#    #+#             */
/*   Updated: 2026/02/11 18:02:02 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tests.h"

int	main(int argc __attribute__((unused)), char **argv __attribute__((unused)), \
	char **envp)
{
	char	*line;
	t_data	*context;

	context = init_shell(envp);
	while (1)
	{
		line = readline("$> ");
		if (line == NULL)
			break ;
		context->root = build_tree_polimorphic();
		print_tree(context->root);
		executor(context->root, context);
		free_context(context);
		free(line);
	}
	free_shell(context);
	return (0);
}

t_data	*init_shell(char **envp)
{
	t_data	*context;

	context = ft_calloc(1, sizeof(t_data));
	context->env = env_to_table(envp);
	context->stdin_backup = dup(STDIN_FILENO);
	context->stdout_backup = dup(STDOUT_FILENO);
	context->root = NULL;
	return (context);
}

void	free_context(t_data *context)
{
	free_tree(context->root);
	context->root = NULL;
	ft_lstclear(&context->fds, close_fd);
	ft_lstclear(&context->pids, close_pid);
}
