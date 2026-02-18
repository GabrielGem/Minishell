/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 11:00:59 by mmaquine          #+#    #+#             */
/*   Updated: 2026/02/18 18:26:29 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_token(t_list *token, t_data *context)
{
	char	*dollar;
	char	*var_name;
	char	*value;
	t_list	*new_token;
	size_t	var_len;

	dollar = ft_strchr(token->content, '$');
	if (!dollar)
		return (token);
	var_name = extract_name(dollar + 1);
	var_len = ft_strlen(var_name);
	if (!ft_strcmp("?", var_name))
		value = ft_itoa(context->exit_status);
	else
	{
		value = hash_search(context->env, var_name, ENV);
		if (!value)
			value = ft_strdup("");
	}
}

static t_list	*expand_variables(t_list *tokens, t_data *context)
{
	t_list	*current;

	current = tokens;
	while (current)
	{
		if ((current->prev && !ft_strcmp("<<", current->prev->content))
		||	is_quote_token(current, '\''))
		{
			current = current->next;
			continue ;
		}
		if (ft_strchr(current->content, '$'))
			current->content = expand_token(current->content, context);
		current = current->next;
	}
}

static t_list	*initial_parser(char *line)
{
	if (!line)
		return (NULL);
	return (ft_lstnew(line));
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
	tokens = initial_parser(line);
	tokens = resolve_quotes(tokens);
	tokens = remove_spaces(tokens);
	tokens = split_token(tokens, "|", NULL);
	tokens = split_token(tokens, ">>", NULL);
	tokens = split_token(tokens, "<<", NULL);
	tokens = split_token(tokens, ">", ">>");
	tokens = split_token(tokens, "<", "<<");
	tokens = expand_variables(tokens, context);
	return (tokens);
}
