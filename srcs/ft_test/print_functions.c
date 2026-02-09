/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 15:23:49 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/06 15:24:21 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tree(t_ast_node *tree)
{
	if (tree == NULL)
		return ;
	if (tree->type.base == NODE_PIPE)
	{
		ft_printf("PIPE:\n");
		print_tree((t_ast_node *)tree->left);
		print_tree((t_ast_node *)tree->right);
	}
	if (tree->type.base == NODE_COMMAND)
	{
		t_command	*cmd = (t_command *)tree;
		t_list		*node = cmd->redirects;
		char 		**args = cmd->args;
		t_redir 	*red;

		ft_printf("  CMD:\n");
		if (args != NULL)
			while (*args)
				ft_printf("\t%s\n", *args++);
		if (node)
		{
			while (node)
			{
				red = (t_redir *)node->content;
				ft_putendl_fd(red->filename, 1);
				node = node->next;
			}
		}
	}
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
