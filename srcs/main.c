/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 09:58:31 by mmaquine          #+#    #+#             */
/*   Updated: 2026/02/22 10:44:21 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tests.h"

volatile sig_atomic_t g_signal_received = 0;

int	main(int argc __attribute__((unused)), char **argv __attribute__((unused)),\
char **env)
{
	t_data	*context;
	char	*prompt;
	char	*line;

	setup_signals_interactive();
	context = init_shell(env);
	prompt = get_prompt_string(context);
	line = readline(prompt);
	free(prompt);
	while (line)
	{
		add_history(line);
		tree_build(line, context);
		context->count_line++;
		context->count_line += hunt_heredoc(context->root, context);
		context->exit_status = executor(context->root, context);
		free_context(context);
		prompt = get_prompt_string(context);
		line = readline(prompt);
		free(prompt);
	}
	free_shell(context);
	rl_clear_history();
	return (0);
}

t_data	*init_shell(char **envp)
{
	t_data	*context;
	char	*home;
	char	*username;

	context = ft_calloc(1, sizeof(t_data));
	context->env = env_to_table(envp);
	home = hash_search(context->env, "HOME", ENV);
	hash_upsert(context->env, "HOME2", home, SET);
	username = hash_search(context->env, "LOGNAME", ENV);
	hash_upsert(context->env, "LOGNAME2", username, SET);
	context->stdin_backup = dup(STDIN_FILENO);
	context->stdout_backup = dup(STDOUT_FILENO);
	context->count_line = 0;
	context->root = NULL;
	return (context);
}

void	free_context(t_data *context)
{
	char	*home;
	char	*username;

	free_tree(context->root);
	context->root = NULL;
	ft_lstclear(&context->fds, close_fd);
	ft_lstclear(&context->pids, close_pid);
	home = hash_search(context->env, "HOME", ENV);
	if (home)
		hash_upsert(context->env, "HOME2", home, SET);
	username = hash_search(context->env, "LOGNAME", ENV);
	if (username)
		hash_upsert(context->env, "LOGNAME2", username, SET);
}
