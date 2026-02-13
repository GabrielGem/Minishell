/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 09:58:31 by mmaquine          #+#    #+#             */
/*   Updated: 2026/02/13 16:14:00 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tests.h"

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

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_data	*context;

	(void)argc;
	(void)argv;
	context = init_shell(env);
	line = NULL;
	line = readline("$> ");
	while (line)
	{
		add_history(line);
		tree_build(line, context);
		line = readline("$> ");
	}
	free_shell(context);
	rl_clear_history();
}
