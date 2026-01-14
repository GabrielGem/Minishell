/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 21:23:58 by mmaquine          #+#    #+#             */
/*   Updated: 2025/08/27 17:07:30 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
The function allocates memory for an array of nmemb elements of size bytes each
and returns a pointer to the allocated memory. The memory is set to zero. If
nmemb or size is 0, then ft_calloc() returns a unique pointer value that can
later be successfully passed to free().
*/
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	total_bytes;

	total_bytes = nmemb * size;
	if (!nmemb || !size)
		return (malloc(sizeof(void *)));
	if ((!nmemb && !size) || (nmemb != total_bytes / size))
		return (NULL);
	ptr = malloc(total_bytes);
	if (!ptr)
		return (NULL);
	ptr = ft_bzero(ptr, nmemb * size);
	return (ptr);
}
