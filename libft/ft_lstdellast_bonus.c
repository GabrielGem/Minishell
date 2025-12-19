/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdellast_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 11:44:49 by mmaquine          #+#    #+#             */
/*   Updated: 2025/11/04 12:42:25 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdellast(t_list *lst, void (*del)(void *))
{
	t_list	*last;

	last = ft_lstlast(lst);
	while (lst->next != last)
		lst = lst->next;
	(*del)(last->content);
	lst->next = NULL;
}
