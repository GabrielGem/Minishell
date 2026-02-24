/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 09:58:31 by mmaquine          #+#    #+#             */
/*   Updated: 2026/02/24 16:40:44 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal_received = 0;

static t_data	*init_shell(char **envp);
static void		run_shell(t_data *context);

int	main(int argc __attribute__((unused)), char **argv __attribute__((unused)), \
char **env)
{
	t_data	*context;

	setup_signals_interactive();
	context = init_shell(env);
	run_shell(context);
	free_shell(context);
	rl_clear_history();
	return (0);
}

static void	run_shell(t_data *context)
{
	char	*prompt;
	char	*line;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			prompt = get_prompt_string(context);
			line = readline(prompt);
			free(prompt);
		}
		else
			line = ft_strtrim(get_next_line(STDIN_FILENO), "\n");
		if (!line)
			break ;
		if (!check_spaces(line))
			add_history(line);
		tree_build(line, context);
		context->count_line += 1 + hunt_heredoc(context->root, context);
		context->exit_status = executor(context->root, context);
		free_context(context);
	}
}

static t_data	*init_shell(char **envp)
{
	t_data	*context;

	context = ft_calloc(1, sizeof(t_data));
	context->env = env_to_table(envp);
	fallback_update(context);
	context->stdin_backup = dup(STDIN_FILENO);
	context->stdout_backup = dup(STDOUT_FILENO);
	context->count_line = 0;
	context->root = NULL;
	return (context);
}
