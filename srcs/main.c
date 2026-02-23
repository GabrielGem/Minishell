/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 09:58:31 by mmaquine          #+#    #+#             */
/*   Updated: 2026/02/23 14:54:28 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal_received = 0;

static void	print_tree(t_node *node, const char *prefix, int is_right, int is_root)
{
	t_ast_node	*pipe_node;
	t_command	*cmd;
	char		new_prefix[4096];
	int			i;

	if (!node)
		return ;
	if (node->base == NODE_PIPE)
	{
		pipe_node = (t_ast_node *)node;
		if (is_root)
		{
			printf("%s(PIPE)\n", prefix);
			snprintf(new_prefix, sizeof(new_prefix), "%s  ", prefix);
		}
		else if (is_right)
		{
			printf("%s╰----(PIPE)\n", prefix);
			snprintf(new_prefix, sizeof(new_prefix), "%s       ", prefix);
		}
		else
		{
			printf("%s|----(PIPE)\n", prefix);
			snprintf(new_prefix, sizeof(new_prefix), "%s|      ", prefix);
		}
		print_tree(pipe_node->left, new_prefix, 0, 0);
		print_tree(pipe_node->right, new_prefix, 1, 0);
	}
	else if (node->base == NODE_COMMAND)
	{
		cmd = (t_command *)node;
		if (is_root)
		{
			i = 0;
			while (cmd->args && cmd->args[i])
			{
				if (i > 0)
					printf(" ");
				printf("%s", cmd->args[i]);
				i++;
			}
			if (!cmd->args || !cmd->args[0])
				printf("(empty)");
			printf("\n");
		}
		else
		{
			if (is_right)
				printf("%s╰----", prefix);
			else
				printf("%s|----", prefix);
			i = 0;
			while (cmd->args && cmd->args[i])
			{
				printf(" %s", cmd->args[i]);
				i++;
			}
			if (!cmd->args || !cmd->args[0])
				printf(" (empty)");
			printf("\n");
		}
	}
}

void	print_ast(t_ast_node *root)
{
	if (!root)
		return ;
	print_tree((t_node *)root, "", 0, 1);
}

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
		prompt = get_prompt_string(context);
		line = readline(prompt);
 		free(prompt);
		if (!line)
			break ;
		if (!check_spaces(line))
			add_history(line);
		tree_build(line, context);
		print_ast(context->root);
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
