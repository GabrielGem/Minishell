/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 13:50:18 by mmaquine          #+#    #+#             */
/*   Updated: 2026/02/13 15:02:43 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*node_last(t_ast_node *lst)
{
	if (!lst)
		return (NULL);
	while (lst->right)
		lst = (t_ast_node *)(lst->right);
	return (lst);
}

// void	ast_node_add_back(t_ast_node **lst, t_ast_node *new)
// {
// 	t_ast_node	*nxt;

// 	if (!lst)
// 		return ;
// 	if (!(*lst))
// 		(*lst) = new;
// 	else
// 	{
// 		nxt = ft_lstlast(*lst);
// 		nxt->right = (t_node *)new;
// 		new->left = (t_node *)nxt;
// 	}
// }
