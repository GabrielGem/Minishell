/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 11:00:59 by mmaquine          #+#    #+#             */
/*   Updated: 2026/02/22 14:47:15 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static	t_quote_state update_state(char **new, char append, t_quote_state st)
{
	append_char(new, append);
	return (st);
}

t_list	*new_initial_parser(char *token)
{
	t_quote_state	state;
	t_list			*lst;
	char			*new;
	int				i;

	state = NORMAL;
	new = NULL;
	lst = NULL;
	i = 0;
	while (token[i])
	{
		if (state == NORMAL)
		{
			if (ft_isspace(token[i]))
			{
				ft_lstadd_back(&lst, ft_lstnew(ft_strdup(new)));
				free(new);
				new = NULL;
			}
			else if (token[i] == '\'')
			{
				append_char(&new, token[i]);
				state = IN_SINGLE_QUOTE;
			}
			else if (token[i] == '\"')
			{
				append_char(&new, token[i]);
				state = IN_DOUBLE_QUOTE;
			}
			else if (token[i] == '<' && token[i + 1] == '<')
			{
				if (new)
				{
					ft_lstadd_back(&lst, ft_lstnew(ft_strdup(new)));
					free(new);
					new = NULL;
				}
				ft_lstadd_back(&lst, ft_lstnew(ft_strdup("<<")));
				i++;
			}
			else if (token[i] == '>' && token[i + 1] == '>')
			{
				if (new)
				{
					ft_lstadd_back(&lst, ft_lstnew(ft_strdup(new)));
					free(new);
					new = NULL;
				}
				ft_lstadd_back(&lst, ft_lstnew(ft_strdup(">>")));
				i++;
			}
			else if (token[i] == '|')
			{
				if (new)
				{
					ft_lstadd_back(&lst, ft_lstnew(ft_strdup(new)));
					free(new);
					new = NULL;
				}
				ft_lstadd_back(&lst, ft_lstnew(ft_strdup("|")));
			}
			else if (token[i] == '>')
			{
				if (new)
				{
					ft_lstadd_back(&lst, ft_lstnew(ft_strdup(new)));
					free(new);
					new = NULL;
				}
				ft_lstadd_back(&lst, ft_lstnew(ft_strdup(">")));
			}
			else if (token[i] == '<')
			{
				if (new)
				{
					ft_lstadd_back(&lst, ft_lstnew(ft_strdup(new)));
					free(new);
					new = NULL;
				}
				ft_lstadd_back(&lst, ft_lstnew(ft_strdup("<")));
			}
			else
				append_char(&new, token[i]);
		}
		else if (state == IN_SINGLE_QUOTE)
		{
			if (token[i] == '\'')
			{
				append_char(&new, token[i]);
				state = NORMAL;
			}
			else
				append_char(&new, token[i]);// adiciona char ao token (tudo é literal aqui)
		}
		else if (state == IN_DOUBLE_QUOTE)
		{
			if (token[i] == '\"')
			{
				append_char(&new, token[i]);
				state = NORMAL;
			}
			else
				append_char(&new, token[i]);// adiciona char ao token (expansao de $ ainda acontece aqui)
		}
		i++;
	}
	if(new)
	{
		ft_lstadd_back(&lst, ft_lstnew(ft_strdup(new)));
		free(new);
	}
	free(token);
	return (lst);
}

t_list	*tokenizer(char *line, t_data *context)
{
	t_list	*tokens;

	if (!line)
		return (NULL);
	if (check_spaces(line))
	{
		free(line);
		return (NULL);
	}
	tokens = new_initial_parser(line);
	tokens = remove_spaces(tokens);
	tokens = expand_token(tokens, context);
	remove_quotes(tokens);
	return (tokens);
}
