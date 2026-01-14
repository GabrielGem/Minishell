/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:36:13 by mmaquine          #+#    #+#             */
/*   Updated: 2025/07/30 15:38:19 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
Counts the number of nodes in the list
lst: The beginnig of the list.
Return the length of the list.
*/
int	ft_lstsize(t_list *lst)
{
	int		l_size;

	l_size = 0;
	while (lst)
	{
		l_size++;
		lst = lst->next;
	}
	return (l_size);
}
