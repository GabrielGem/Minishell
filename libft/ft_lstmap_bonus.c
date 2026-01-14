/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:18:57 by mmaquine          #+#    #+#             */
/*   Updated: 2025/09/04 10:36:52 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
Iterates through the list 'lst', applies the function 'f' to each node's content
and creates a new list resulting of the successive applications of the function
'f'. The 'del' function is used to delete the content of a node if needed.
lst: The address of a pointer to a node.
f: The address of the function applied to each node's content .
del: The address of the function used to delete a node's content if neede
*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first;
	t_list	*nxt;

	if (!lst || !f || !del)
		return (NULL);
	first = ft_lstnew((*f)(lst->content));
	if (!first)
		return (NULL);
	nxt = first;
	lst = lst->next;
	while (lst)
	{
		nxt->next = ft_lstnew((*f)(lst->content));
		if (!nxt->next)
		{
			ft_lstclear(&first, del);
			return (NULL);
		}
		nxt->prev = lst;
		lst = lst->next;
		nxt = nxt->next;
	}
	return (first);
}
