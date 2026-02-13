/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_after.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 15:48:41 by mmaquine          #+#    #+#             */
/*   Updated: 2025/12/23 17:17:40 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	Add element after right after element current.
*/
void	ft_lstadd_after(t_list *current, t_list *after)
{
	if (!current || !after)
		return ;
	if (!current->next)
	{
		ft_lstadd_front(&current, after);
		return ;
	}
	after->next = current->next;
	after->prev = current;
	current->next->prev = after;
	current->next = after;
}
