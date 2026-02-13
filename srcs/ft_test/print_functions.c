/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 15:23:49 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/13 14:22:56 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Lembre-se de incluir a sua libft ou o header que contém ft_bzero, ft_putstr_fd, etc.

static void	ft_print_ast_node(t_node *node, int depth, char *prefix, int is_last_child);
static void	ft_add_space(char new_prefix[256], int *prefix_idx);
static void	ft_add_column(char new_prefix[256], int *prefix_idx);
static void	ft_print_content(t_node *node, int depth, char *prefix, int is_last_child);

/* Função principal. Agora recebe o root do tipo t_ast_node (ou t_node) */
void	ft_print_ast(t_ast_node *root)
{
	if (!root)
		return ;
	ft_print_ast_node((t_node *)root, 0, "", 1);
}

static void	ft_print_ast_node(t_node *node, int depth, char *prefix, int is_last_child)
{
	t_ast_node	*ast_node;
	char		new_prefix[256];
	int			prefix_idx;

	if (!node)
		return ;
		
	ft_bzero(new_prefix, 256 * sizeof(char));
	
	/* Imprime o conteúdo do nó atual (PIPE ou COMMAND) */
	ft_print_content(node, depth, prefix, is_last_child);

	/* Se for um comando, ele é uma "folha" (não tem filhos left/right), então paramos aqui */
	if (node->base == NODE_COMMAND)
		return ;

	/* Se for um PIPE, preparamos o prefixo para imprimir os filhos */
	prefix_idx = -1;
	while (prefix[++prefix_idx] && prefix_idx < 255)
		new_prefix[prefix_idx] = prefix[prefix_idx];
		
	if (is_last_child)
		ft_add_space(new_prefix, &prefix_idx);
	else
		ft_add_column(new_prefix, &prefix_idx);

	/* Fazemos o cast seguro para t_ast_node para acessar ->left e ->right */
	ast_node = (t_ast_node *)node;
	
	if (ast_node->left)
		ft_print_ast_node(ast_node->left, depth + 1, new_prefix, ast_node->right == NULL);
	if (ast_node->right)
		ft_print_ast_node(ast_node->right, depth + 1, new_prefix, 1);
}

static void	ft_add_space(char new_prefix[256], int *prefix_idx)
{
	new_prefix[(*prefix_idx)++] = ' ';
	new_prefix[(*prefix_idx)++] = ' ';
	new_prefix[(*prefix_idx)++] = ' ';
	new_prefix[(*prefix_idx)++] = ' ';
}

static void	ft_add_column(char new_prefix[256], int *prefix_idx)
{
	new_prefix[(*prefix_idx)++] = '\xe2';
	new_prefix[(*prefix_idx)++] = '\x94';
	new_prefix[(*prefix_idx)++] = '\x82';
	new_prefix[(*prefix_idx)++] = ' ';
	new_prefix[(*prefix_idx)++] = ' ';
	new_prefix[(*prefix_idx)++] = ' ';
}

static void	ft_print_content(t_node *node, int depth, char *prefix, int is_last_child)
{
	int			i;
	t_command	*cmd;

	if (depth > 0)
	{
		/* Removi o 'prefix + 4' do original por segurança de memória */
		ft_putstr_fd(prefix, 1);
		if (is_last_child)
			ft_putstr_fd("└── ", 1);
		else
			ft_putstr_fd("├── ", 1);
	}
	
	ft_putstr_fd("(", 1);
	
	/* Verifica se o nó é um PIPE */
	if (node->base == NODE_PIPE)
		ft_putstr_fd("PIPE", 1);
		
	/* Verifica se o nó é um COMANDO */
	else if (node->base == NODE_COMMAND)
	{
		cmd = (t_command *)node;
		if (cmd->is_builtin)
			ft_putstr_fd("BUILTIN: ", 1);
		
		i = 0;
		while (cmd->args && cmd->args[i])
		{
			ft_putstr_fd(cmd->args[i], 1);
			if (cmd->args[i + 1])
				ft_putstr_fd(" ", 1);
			i++;
		}
	}
	
	ft_putstr_fd(")\n", 1);
}

void print_hash_table(t_hash_table *table)
{
    if (!table || !table->items)
    {
        printf("Tabela vazia ou não inicializada.\n");
        return;
    }

    printf("--- Conteúdo da Tabela Hash (%d/%d itens) ---\n", table->count, table->size);

    for (int i = 0; i < table->size; i++)
    {
        t_hash_item *current = table->items[i];

        // Só printamos o índice se ele contiver algum item (opcional)
        if (current)
        {
            printf("Bucket [%d]: ", i);
            while (current)
            {
                printf("[%s = %s (Tag: %s)]", 
                    current->key, 
                    current->value ? current->value : "NULL",
                    current->tag == ENV ? "ENV" : "EXPORT");

                if (current->next)
                    printf(" -> ");
                
                current = current->next;
            }
            printf("\n");
        }
    }
    printf("-------------------------------------------\n");
}
