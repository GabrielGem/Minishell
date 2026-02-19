/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 09:37:13 by mmaquine          #+#    #+#             */
/*   Updated: 2026/02/19 15:49:53 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Remove var_name from old string and insert new where var_name start
*/
static char	*reshape_string(char *old, char *var_name, char *new, size_t start)
{
	char	*lstr;
	char	*rstr;
	char	*newstr;

	if (!old || !var_name)
		return (old);
	lstr = ft_substr(old, 0, ft_strlen(old) - start);
	rstr = ft_substr(old, start, ft_strlen(old));
	newstr = NULL;
	if (!ft_strlen(lstr))
	{
		free(lstr);
		lstr = NULL;
	}
	if (!ft_strlen(rstr))
	{
		free(rstr);
		rstr = NULL;
	}
	str_append(&newstr, lstr);
	str_append(&newstr, new);
	str_append(&newstr, rstr);
	return (newstr);
}

/*
Expands first ocurrence of $.
*/
char	*expand_variable(char *token, t_data *context)
{
	char	*dollar;
	char	*var_name;
	char	*value;
	char	*new_str;

	dollar = ft_strchr(token, '$');
	if (!dollar)
		return (token);
	var_name = extract_name(dollar + 1);
	if (!ft_strcmp("?", var_name))
		value = ft_itoa(context->exit_status);	
	else
	{
		value = hash_search(context->env, var_name, ENV);
		if (!value)
			value = ft_strdup("");
	}
	new_str = reshape_string(token, var_name, value, ft_strlen(var_name) + 1);
	free(value);
	free(var_name);
	return (new_str);
}

/*
Expands variables (if any) on a given token
*/
t_list	*expand_token(t_list *tokens, t_data *context)
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
		{
			current->content = expand_variable(current->content, context);
			continue ;
		}
		current = current->next;
	}
	return (tokens);
}
