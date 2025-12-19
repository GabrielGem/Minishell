/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 09:19:01 by mmaquine          #+#    #+#             */
/*   Updated: 2025/07/29 11:25:07 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Applies the function f to each character of the string s, passing its index as
first argument and the character itself as te second. A new string is created
(using malloc(3)) to store the results from the successive applications of f.
*/
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char			*mapped;
	unsigned int	i;

	if (s == NULL || f == NULL)
		return (NULL);
	mapped = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!mapped)
		return (NULL);
	i = 0;
	while (s[i])
	{
		mapped[i] = (*f)(i, s[i]);
		i++;
	}
	mapped[i] = '\0';
	return (mapped);
}
