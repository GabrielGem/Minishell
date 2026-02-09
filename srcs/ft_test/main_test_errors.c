/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 by test                      #+#    #+#             */
/*   Updated: 2026/02/07 13:47:51 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

// Declaração das funções de teste
t_ast_node	*test_file_not_found_input(void);
t_ast_node	*test_permission_denied_input(void);
t_ast_node	*test_permission_denied_output(void);
t_ast_node	*test_redirect_to_directory(void);
t_ast_node	*test_command_not_found(void);
t_ast_node	*test_command_not_executable(void);
t_ast_node	*test_pipe_first_cmd_fail(void);
t_ast_node	*test_pipe_second_cmd_fail(void);
t_ast_node	*test_multiple_redirects_with_error(void);
t_ast_node	*test_export_no_args(void);
t_ast_node	*test_export_invalid_identifier(void);
t_ast_node	*test_pipe_with_failed_redirect(void);
t_ast_node	*test_absolute_path_not_found(void);
t_ast_node	*test_directory_as_command(void);
t_ast_node	*test_empty_redirect_filename(void);

typedef struct s_test
{
	char		*name;
	char		*description;
	t_ast_node	*(*func)(void);
}	t_test;

void	print_menu(t_test *tests, int count)
{
	int	i;

	printf("\n╔════════════════════════════════════════════════════════════╗\n");
	printf("║          BATERIA DE TESTES DE ERRO - MINISHELL           ║\n");
	printf("╠════════════════════════════════════════════════════════════╣\n");
	
	for (i = 0; i < count; i++)
	{
		printf("║ %2d. %-54s ║\n", i + 1, tests[i].name);
	}
	
	printf("║  0. Executar todos os testes                             ║\n");
	printf("║ -1. Sair                                                 ║\n");
	printf("╚════════════════════════════════════════════════════════════╝\n");
	printf("\nEscolha um teste: ");
}

void	print_test_header(char *name, char *description)
{
	printf("\n┌────────────────────────────────────────────────────────────┐\n");
	printf("│ TESTE: %-50s │\n", name);
	printf("│ DESC:  %-50s │\n", description);
	printf("└────────────────────────────────────────────────────────────┘\n");
}

void	run_test(t_test *test, t_data *context)
{
	t_ast_node	*tree;
	
	print_test_header(test->name, test->description);
	tree = test->func();
	
	printf("\n🔧 Executando árvore AST...\n");
	printf("─────────────────────────────────────────────────────────────\n");
	
	// Executa a árvore usando o executor do minishell
	context->root = tree;
	executor(context->root, context);
	
	printf("─────────────────────────────────────────────────────────────\n");
	printf("✓ Teste concluído. Exit status: %d\n", context->exit_status);
	
	// Limpeza da árvore
	free_context(context);
}

int	main(int argc, char **argv, char **envp)
{
	t_test	tests[] = {
		{
			"Arquivo não encontrado (input)",
			"cat < arquivo_inexistente",
			test_file_not_found_input
		},
		{
			"Sem permissão (input)",
			"cat < /etc/shadow",
			test_permission_denied_input
		},
		{
			"Sem permissão (output)",
			"echo test > /root/arquivo.txt",
			test_permission_denied_output
		},
		{
			"Redirecionar para diretório",
			"echo test > /tmp",
			test_redirect_to_directory
		},
		{
			"Comando não encontrado",
			"comando_inexistente",
			test_command_not_found
		},
		{
			"Comando não executável",
			"/etc/passwd (arquivo não executável)",
			test_command_not_executable
		},
		{
			"Pipe - primeiro comando falha",
			"comando_inexistente | wc -l",
			test_pipe_first_cmd_fail
		},
		{
			"Pipe - segundo comando falha",
			"ls | comando_inexistente",
			test_pipe_second_cmd_fail
		},
		{
			"Múltiplos redirects com erro",
			"cat < hosts < inexistente > saida",
			test_multiple_redirects_with_error
		},
		{
			"Export sem argumentos",
			"export (deve listar variáveis)",
			test_export_no_args
		},
		{
			"Export - identificador inválido",
			"export 123VAR=value",
			test_export_invalid_identifier
		},
		{
			"Pipe com redirect que falha",
			"ls | cat > /root/arquivo.txt",
			test_pipe_with_failed_redirect
		},
		{
			"Caminho absoluto não encontrado",
			"/usr/bin/comando_inexistente",
			test_absolute_path_not_found
		},
		{
			"Diretório como comando",
			"/usr/bin (executar diretório)",
			test_directory_as_command
		},
		{
			"Nome de arquivo vazio",
			"echo test > \"\"",
			test_empty_redirect_filename
		}
	};
	
	int		count = sizeof(tests) / sizeof(tests[0]);
	int		choice;
	int		i;
	t_data	*context;
	
	(void)argc;
	(void)argv;
	
	// Inicializa o contexto do minishell
	context = init_shell(envp);
	
	while (1)
	{
		print_menu(tests, count);
		
		if (scanf("%d", &choice) != 1)
		{
			while (getchar() != '\n');
			printf("❌ Entrada inválida!\n");
			continue;
		}
		while (getchar() != '\n');
		
		if (choice == -1)
		{
			printf("\n👋 Saindo...\n");
			break;
		}
		else if (choice == 0)
		{
			printf("\n🚀 Executando todos os testes...\n");
			for (i = 0; i < count; i++)
			{
				run_test(&tests[i], context);
				printf("\nPressione ENTER para continuar...");
				getchar();
			}
			printf("\n✅ Todos os testes foram executados!\n");
		}
		else if (choice > 0 && choice <= count)
		{
			run_test(&tests[choice - 1], context);
		}
		else
		{
			printf("❌ Opção inválida!\n");
		}
	}
	
	// Limpeza final
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
