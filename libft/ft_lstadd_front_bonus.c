/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:19:52 by mmaquine          #+#    #+#             */
/*   Updated: 2025/11/03 21:22:28 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
Adds the node 'new' at the beginning of the list.
lst: The address of a pointer to the first node of a list.
new: The address of a pointer to the node to be added.
*/
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!(*lst))
		(*lst) = new;
	else
	{
		new->next = (*lst);
		new->prev = NULL;
		(*lst)->prev = new;
		(*lst) = new;
	}
}
