/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_array_of_pointers.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 13:18:06 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/01/30 11:31:54 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_size(void **array);

void	**ft_join_array_of_pointers(void **a1, void **a2)
{
	void	**new_array;
	int		size;
	int		i;

	if (!a1 || !a2)
		return (NULL);
	size = count_size(a1);
	size += count_size(a2);
	new_array = ft_calloc(size + 1, sizeof (void *));
	if (!new_array)
		return (NULL);
	i = 0;
	while (*a1)
		new_array[i++] = *a1++;
	while (*a2)
		new_array[i++] = *a2++;
	return (new_array);
}

static int	count_size(void **array)
{
	int	count;

	count = 0;
	while (*array)
	{
		count++;
		array++;
	}
	return (count);
}
