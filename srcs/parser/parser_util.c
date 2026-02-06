/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 10:57:20 by mmaquine          #+#    #+#             */
/*   Updated: 2026/02/03 19:24:25 by mmaquine         ###   ########.fr       */
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
Return: 1 if only has spaces, 0 otherwise
*/
int	check_spaces(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = -1;
	while (line[++i])
		if (!ft_isspace(line[i]))
			return (0);
	return (1);
}

char	is_quote_token(t_list *token, char tkn)
{
	char	*str;

	if (!token || !token->content)
		return (0);
	str = token->content;
	if (str[0] == tkn && str[ft_strlen(str) - 1] == tkn)
		return (1);
	return (0);
}

void	insert_new_tokens(t_list **hd, t_list *lt, t_list *md, t_list *rt)
{
	if (lt)
	{
		lt->next = md;
		md->prev = lt;
	}
	else if (hd)
		*hd = md;
	(ft_lstlast(md))->next = rt;
	if (rt)
		rt->prev = ft_lstlast(md);
}
