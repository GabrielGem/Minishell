/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 13:31:00 by mmaquine          #+#    #+#             */
/*   Updated: 2025/09/30 14:14:31 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Free all memory alocated in a double-pointer char terminated with NULL.
Returns the number of pointer(s) freed.
*/
int	ft_free_split(char **split)
{
	int	freed;

	if (!split)
		return (0);
	freed = 0;
	while (split[freed])
	{
		free(split[freed]);
		freed++;
	}
	free(split);
	return (freed);
}
