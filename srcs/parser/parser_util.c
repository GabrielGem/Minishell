/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 10:57:20 by mmaquine          #+#    #+#             */
/*   Updated: 2026/01/22 16:23:12 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	str_append(char **str1, char *str2)
{
	char	*append;

	append = ft_strjoin(*str1, str2);
	free(*str1);
	*str1 = append;
}

/*
Verify if lines only has spaces
*/
int	check_spaces(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = -1;
	while (line[++i])
		if (ft_isspace(line[i]))
			return (0);
	return (1);
}

/*
	Separate current string in 3 (at most) strings and insert
	on the list. Frees the separated token content
*/
// t_list	*tear_string(t_list *token, char *start, char *end)
// {
// 	t_list	*new_tokens;
// 	char	*lstr;
// 	char	*rstr;

// 	lstr = NULL;
// 	rstr = NULL;
// 	lstr = ft_substr(token->content, 0, end - start);
// }
