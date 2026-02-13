/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_error_cases.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 by test                      #+#    #+#             */
/*   Updated: 2026/02/07 by test                     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
 * TESTE 1: Arquivo de redirecionamento não existe (REDIN)
 * Comando: cat < arquivo_inexistente
 * Erro esperado: "minishell: arquivo_inexistente: No such file or directory"
 * Exit status: 1
 */
t_ast_node	*test_file_not_found_input(void)
{
	t_command	*cmd;
	t_redir		*redir;

	cmd = ft_calloc(1, sizeof(t_command));
	cmd->type.base = NODE_COMMAND;
	cmd->args = ft_calloc(3, sizeof(char *));
	cmd->args[0] = ft_strdup("/bin/cat");
	cmd->args[1] = ft_strdup("cat");
	cmd->args[2] = NULL;

	redir = ft_calloc(1, sizeof(t_redir));
	redir->type = REDIN;
	redir->filename = ft_strdup("arquivo_que_nao_existe.txt");
	ft_lstadd_back(&cmd->redirects, ft_lstnew(redir));

	return ((t_ast_node *)cmd);
}

/* 
 * TESTE 2: Sem permissão para ler arquivo (REDIN)
 * Comando: cat < /etc/shadow (ou outro arquivo sem permissão)
 * Erro esperado: "minishell: /etc/shadow: Permission denied"
 * Exit status: 1
 */
t_ast_node	*test_permission_denied_input(void)
{
	t_command	*cmd;
	t_redir		*redir;

	cmd = ft_calloc(1, sizeof(t_command));
	cmd->type.base = NODE_COMMAND;
	cmd->args = ft_calloc(3, sizeof(char *));
	cmd->args[0] = ft_strdup("/bin/cat");
	cmd->args[1] = ft_strdup("cat");
	cmd->args[2] = NULL;

	redir = ft_calloc(1, sizeof(t_redir));
	redir->type = REDIN;
	redir->filename = ft_strdup("/etc/shadow");
	ft_lstadd_back(&cmd->redirects, ft_lstnew(redir));

	return ((t_ast_node *)cmd);
}

/* 
 * TESTE 3: Sem permissão para escrever (REDOUT)
 * Comando: echo test > /root/arquivo.txt
 * Erro esperado: "minishell: /root/arquivo.txt: Permission denied"
 * Exit status: 1
 */
t_ast_node	*test_permission_denied_output(void)
{
	t_command	*cmd;
	t_redir		*redir;

	cmd = ft_calloc(1, sizeof(t_command));
	cmd->type.base = NODE_COMMAND;
	cmd->args = ft_calloc(4, sizeof(char *));
	cmd->args[0] = ft_strdup("/bin/echo");
	cmd->args[1] = ft_strdup("echo");
	cmd->args[2] = ft_strdup("test");
	cmd->args[3] = NULL;

	redir = ft_calloc(1, sizeof(t_redir));
	redir->type = REDOUT;
	redir->filename = ft_strdup("/root/arquivo_teste.txt");
	ft_lstadd_back(&cmd->redirects, ft_lstnew(redir));

	return ((t_ast_node *)cmd);
}

/* 
 * TESTE 4: Tentar redirecionar para um diretório
 * Comando: echo test > /tmp
 * Erro esperado: "minishell: /tmp: Is a directory"
 * Exit status: 1
 */
t_ast_node	*test_redirect_to_directory(void)
{
	t_command	*cmd;
	t_redir		*redir;

	cmd = ft_calloc(1, sizeof(t_command));
	cmd->type.base = NODE_COMMAND;
	cmd->args = ft_calloc(4, sizeof(char *));
	cmd->args[0] = ft_strdup("/bin/echo");
	cmd->args[1] = ft_strdup("echo");
	cmd->args[2] = ft_strdup("test");
	cmd->args[3] = NULL;

	redir = ft_calloc(1, sizeof(t_redir));
	redir->type = REDOUT;
	redir->filename = ft_strdup("/tmp");
	ft_lstadd_back(&cmd->redirects, ft_lstnew(redir));

	return ((t_ast_node *)cmd);
}

/* 
 * TESTE 5: Comando não encontrado
 * Comando: comando_inexistente
 * Erro esperado: "minishell: comando_inexistente: command not found"
 * Exit status: 127
 */
t_ast_node	*test_command_not_found(void)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	cmd->type.base = NODE_COMMAND;
	cmd->args = ft_calloc(2, sizeof(char *));
	cmd->args[0] = ft_strdup("comando_que_nao_existe");
	cmd->args[1] = NULL;

	return ((t_ast_node *)cmd);
}

/* 
 * TESTE 6: Comando sem permissão de execução
 * Comando: /etc/passwd (tentar executar arquivo que não é executável)
 * Erro esperado: "minishell: /etc/passwd: Permission denied"
 * Exit status: 126
 */
t_ast_node	*test_command_not_executable(void)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	cmd->type.base = NODE_COMMAND;
	cmd->args = ft_calloc(2, sizeof(char *));
	cmd->args[0] = ft_strdup("/etc/passwd");
	cmd->args[1] = NULL;

	return ((t_ast_node *)cmd);
}

/* 
 * TESTE 7: Pipe com erro no primeiro comando
 * Comando: comando_inexistente | wc -l
 * Erro esperado: "minishell: comando_inexistente: command not found"
 * Exit status: último comando do pipe (0 se wc funcionar)
 */
t_ast_node	*test_pipe_first_cmd_fail(void)
{
	t_command	*cmd1;
	t_command	*cmd2;
	t_ast_node	*pipe_node;

	cmd1 = ft_calloc(1, sizeof(t_command));
	cmd1->type.base = NODE_COMMAND;
	cmd1->args = ft_calloc(2, sizeof(char *));
	cmd1->args[0] = ft_strdup("comando_inexistente");
	cmd1->args[1] = NULL;

	cmd2 = ft_calloc(1, sizeof(t_command));
	cmd2->type.base = NODE_COMMAND;
	cmd2->args = ft_calloc(4, sizeof(char *));
	cmd2->args[0] = ft_strdup("/usr/bin/wc");
	cmd2->args[1] = ft_strdup("wc");
	cmd2->args[2] = ft_strdup("-l");
	cmd2->args[3] = NULL;

	pipe_node = ft_calloc(1, sizeof(t_ast_node));
	pipe_node->type.base = NODE_PIPE;
	pipe_node->left = (t_node *)cmd1;
	pipe_node->right = (t_node *)cmd2;

	return (pipe_node);
}

/* 
 * TESTE 8: Pipe com erro no segundo comando
 * Comando: ls | comando_inexistente
 * Erro esperado: "minishell: comando_inexistente: command not found"
 * Exit status: 127
 */
t_ast_node	*test_pipe_second_cmd_fail(void)
{
	t_command	*cmd1;
	t_command	*cmd2;
	t_ast_node	*pipe_node;

	cmd1 = ft_calloc(1, sizeof(t_command));
	cmd1->type.base = NODE_COMMAND;
	cmd1->args = ft_calloc(3, sizeof(char *));
	cmd1->args[0] = ft_strdup("/bin/ls");
	cmd1->args[1] = ft_strdup("ls");
	cmd1->args[2] = NULL;

	cmd2 = ft_calloc(1, sizeof(t_command));
	cmd2->type.base = NODE_COMMAND;
	cmd2->args = ft_calloc(2, sizeof(char *));
	cmd2->args[0] = ft_strdup("comando_inexistente");
	cmd2->args[1] = NULL;

	pipe_node = ft_calloc(1, sizeof(t_ast_node));
	pipe_node->type.base = NODE_PIPE;
	pipe_node->left = (t_node *)cmd1;
	pipe_node->right = (t_node *)cmd2;

	return (pipe_node);
}

/* 
 * TESTE 9: Múltiplos redirecionamentos com erro
 * Comando: cat < arquivo1 < arquivo_inexistente > saida.txt
 * Erro esperado: erro no segundo arquivo de entrada
 * Exit status: 1
 */
t_ast_node	*test_multiple_redirects_with_error(void)
{
	t_command	*cmd;
	t_redir		*redir1;
	t_redir		*redir2;
	t_redir		*redir3;

	cmd = ft_calloc(1, sizeof(t_command));
	cmd->type.base = NODE_COMMAND;
	cmd->args = ft_calloc(3, sizeof(char *));
	cmd->args[0] = ft_strdup("/bin/cat");
	cmd->args[1] = ft_strdup("cat");
	cmd->args[2] = NULL;

	// Primeiro redirect (existe)
	redir1 = ft_calloc(1, sizeof(t_redir));
	redir1->type = REDIN;
	redir1->filename = ft_strdup("/etc/hosts");
	ft_lstadd_back(&cmd->redirects, ft_lstnew(redir1));

	// Segundo redirect (não existe - deve dar erro)
	redir2 = ft_calloc(1, sizeof(t_redir));
	redir2->type = REDIN;
	redir2->filename = ft_strdup("arquivo_inexistente.txt");
	ft_lstadd_back(&cmd->redirects, ft_lstnew(redir2));

	// Terceiro redirect (saída)
	redir3 = ft_calloc(1, sizeof(t_redir));
	redir3->type = REDOUT;
	redir3->filename = ft_strdup("saida.txt");
	ft_lstadd_back(&cmd->redirects, ft_lstnew(redir3));

	return ((t_ast_node *)cmd);
}

/* 
 * TESTE 10: Export sem argumentos (deve imprimir variáveis)
 * Comando: export
 * Erro esperado: nenhum (deve funcionar)
 * Exit status: 0
 */
t_ast_node	*test_export_no_args(void)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	cmd->type.base = NODE_COMMAND;
	cmd->is_builtin = B_EXPORT;
	cmd->args = ft_calloc(2, sizeof(char *));
	cmd->args[0] = ft_strdup("export");
	cmd->args[1] = NULL;

	return ((t_ast_node *)cmd);
}

/* 
 * TESTE 11: Export com nome de variável inválido
 * Comando: export 123VAR=value
 * Erro esperado: "minishell: export: `123VAR=value': not a valid identifier"
 * Exit status: 1
 */
t_ast_node	*test_export_invalid_identifier(void)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	cmd->type.base = NODE_COMMAND;
	cmd->is_builtin = B_EXPORT;
	cmd->args = ft_calloc(3, sizeof(char *));
	cmd->args[0] = ft_strdup("export");
	cmd->args[1] = ft_strdup("123VAR=value");
	cmd->args[2] = NULL;

	return ((t_ast_node *)cmd);
}

/* 
 * TESTE 12: Pipe com redirecionamento que falha
 * Comando: ls | cat > /root/arquivo.txt
 * Erro esperado: "minishell: /root/arquivo.txt: Permission denied"
 * Exit status: 1
 */
t_ast_node	*test_pipe_with_failed_redirect(void)
{
	t_command	*cmd1;
	t_command	*cmd2;
	t_redir		*redir;
	t_ast_node	*pipe_node;

	cmd1 = ft_calloc(1, sizeof(t_command));
	cmd1->type.base = NODE_COMMAND;
	cmd1->args = ft_calloc(3, sizeof(char *));
	cmd1->args[0] = ft_strdup("/bin/ls");
	cmd1->args[1] = ft_strdup("ls");
	cmd1->args[2] = NULL;

	cmd2 = ft_calloc(1, sizeof(t_command));
	cmd2->type.base = NODE_COMMAND;
	cmd2->args = ft_calloc(3, sizeof(char *));
	cmd2->args[0] = ft_strdup("/bin/cat");
	cmd2->args[1] = ft_strdup("cat");
	cmd2->args[2] = NULL;

	redir = ft_calloc(1, sizeof(t_redir));
	redir->type = REDOUT;
	redir->filename = ft_strdup("/root/arquivo.txt");
	ft_lstadd_back(&cmd2->redirects, ft_lstnew(redir));

	pipe_node = ft_calloc(1, sizeof(t_ast_node));
	pipe_node->type.base = NODE_PIPE;
	pipe_node->left = (t_node *)cmd1;
	pipe_node->right = (t_node *)cmd2;

	return (pipe_node);
}

/* 
 * TESTE 13: Caminho absoluto errado
 * Comando: /usr/bin/comando_inexistente
 * Erro esperado: "minishell: /usr/bin/comando_inexistente: No such file or directory"
 * Exit status: 127
 */
t_ast_node	*test_absolute_path_not_found(void)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	cmd->type.base = NODE_COMMAND;
	cmd->args = ft_calloc(2, sizeof(char *));
	cmd->args[0] = ft_strdup("/usr/bin/comando_inexistente");
	cmd->args[1] = NULL;

	return ((t_ast_node *)cmd);
}

/* 
 * TESTE 14: Diretório como comando
 * Comando: /usr/bin (executar um diretório)
 * Erro esperado: "minishell: /usr/bin: Is a directory"
 * Exit status: 126
 */
t_ast_node	*test_directory_as_command(void)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	cmd->type.base = NODE_COMMAND;
	cmd->args = ft_calloc(2, sizeof(char *));
	cmd->args[0] = ft_strdup("/usr/bin");
	cmd->args[1] = NULL;

	return ((t_ast_node *)cmd);
}

/*
 * TESTE 15: Arquivo vazio como nome de redirecionamento
 * Comando: echo test > ""
 * Erro esperado: "minishell: : No such file or directory"
 * Exit status: 1
 */
t_ast_node	*test_empty_redirect_filename(void)
{
	t_command	*cmd;
	t_redir		*redir;

	cmd = ft_calloc(1, sizeof(t_command));
	cmd->type.base = NODE_COMMAND;
	cmd->args = ft_calloc(4, sizeof(char *));
	cmd->args[0] = ft_strdup("/bin/echo");
	cmd->args[1] = ft_strdup("echo");
	cmd->args[2] = ft_strdup("test");
	cmd->args[3] = NULL;

	redir = ft_calloc(1, sizeof(t_redir));
	redir->type = REDOUT;
	redir->filename = ft_strdup("");
	ft_lstadd_back(&cmd->redirects, ft_lstnew(redir));

	return ((t_ast_node *)cmd);
}
