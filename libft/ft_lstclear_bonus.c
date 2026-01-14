/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:42:11 by mmaquine          #+#    #+#             */
/*   Updated: 2025/07/30 17:10:23 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
Deletes and frees the given node and all its successors, using the function 
'del' and free(3). Finally, set the pointer to the list to NULL.
lst: The address of a pointer to a node.
del: The address of the function used to delete the content of the node.
*/
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*l;
	t_list	*to_del;

	if (!lst || !del)
		return ;
	to_del = (*lst);
	while (to_del)
	{
		l = to_del->next;
		ft_lstdelone(to_del, del);
		to_del = l;
	}
	*lst = NULL;
}
