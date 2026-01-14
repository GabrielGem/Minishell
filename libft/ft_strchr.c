/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:10:47 by mmaquine          #+#    #+#             */
/*   Updated: 2025/07/30 13:11:58 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
The function returns a pointer to the first occurence of the character c in the
string s.
Return a pointer to the matched character or NULL if the character is not found
*/
char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	else
		return (NULL);
}

/*
#include <stdio.h>
#include <bsd/string.h>
int	main()
{
	char *s = "teste";
	
	printf("%c\n", s[5]);
	printf("%s\n", ft_strchr(s, 1024));
}*/