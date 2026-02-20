/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 10:57:20 by mmaquine          #+#    #+#             */
/*   Updated: 2026/02/19 15:24:37 by mmaquine         ###   ########.fr       */
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

/*
Insert a t_list (can be a list with more than one element) md betweeen lt and 
rt t_list elements
*/
void	insert_new_tokens(t_list **hd, t_list *lt, t_list *md, t_list *rt)
{
	t_list	*last_md;

	last_md = ft_lstlast(md);
	if (lt)
	{
		lt->next = md;
		md->prev = lt;
	}
	last_md->next = rt;
	if (rt)
	rt->prev = last_md;
	if (hd)
		*hd = ft_lstfirst(md);
}

/*
Returns a variable name. NULL if it starts with no ? or [a-zA-Z_]
*/
char	*extract_name(char	*token)
{
	int		i;
	char	*name;

	if (!token)
		return (NULL);
	if (!(ft_isalpha(token[0]) || (token[0] != '_')))
		return (NULL);
	i = 0;
	while (token[i] && (ft_isalnum(token[i]) || token[i] == '_'))
		i++;
	name = ft_substr(token, 0, i);
	if (name && !ft_strlen(name))
	{
		free(name);
		name = NULL;
	}
	return (name);
}
