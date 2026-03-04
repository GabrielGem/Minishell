/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 10:57:20 by mmaquine          #+#    #+#             */
/*   Updated: 2026/03/04 16:00:11 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Append str2 at end of str1.
*/
void	str_append(char **str1, char *str2)
{
	char	*append;

	append = ft_strjoin(*str1, str2);
	free(*str1);
	*str1 = append;
}

/*
Append a single char to the end of str1, if str1 is NULL c will be the first
char.
*/
void	append_char(char **str1, char c)
{
	char	str[2];

	str[0] = c;
	str[1] = '\0';
	str_append(str1, str);
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

/*
Returns a variable name. NULL if it starts with no ? or [a-zA-Z_]
*/
char	*extract_name(char	*token)
{
	int		i;
	char	*name;

	if (!token)
		return (NULL);
	if (!ft_isalpha(token[0]) && *token != '_')
		return (NULL);
	if (token[0] == '?')
		return (ft_strdup("?"));
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
