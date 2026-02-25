/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_before.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:46:32 by mmaquine          #+#    #+#             */
/*   Updated: 2025/12/29 13:56:13 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	Add element new right before current. If current is the root node then
	ft_lstadd_back is called instead.
*/
void	ft_lstadd_before(t_list *current, t_list *new)
{
	if (!current || !new)
		return ;
	if (!current->prev)
	{
		ft_lstadd_back(&current, new);
		return ;
	}
	new->next = current;
	new->prev = current->prev;
	current->prev->next = new;
	current->prev = new;
}
