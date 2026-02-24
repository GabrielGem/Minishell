/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 09:37:13 by mmaquine          #+#    #+#             */
/*   Updated: 2026/02/23 20:42:16 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Remove var_name from old string and insert new where var_name start
*/
static char	*reshape_string(char *old, char *var, char *value, size_t start)
{
	char	*lstr;
	char	*rstr;
	char	*newstr;

	if (!old || !var)
		return (old);
	lstr = ft_substr(old, 0, start);
	rstr = ft_substr(old, start + ft_strlen(var) + 1, ft_strlen(old));
	newstr = NULL;
	str_append(&newstr, lstr);
	str_append(&newstr, value);
	str_append(&newstr, rstr);
	free(old);
	free(lstr);
	free(rstr);
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
	else if (token[1] == ' ')
		return (token);
	else
	{
		value = ft_strdup(hash_search(context->env, var_name, ENV));
		if (!value)
			value = ft_strdup("");
	}
	new_str = reshape_string(token, var_name, value, dollar - token);
	free(value);
	free(var_name);
	return (new_str);
}

/*
Expand tilde with the same content $HOME usually stores
*/
static char	*expand_tilde(char	*old, t_data *context)
{
	char	*new;
	char	*value;
	char	*old_w_dollar;

	if (!old)
		return (old);
	if (old[0] == '~' && old[1] == '~')
		return (old);
	if (old[0] != '~')
		return (old);
	old_w_dollar = NULL;
	str_append(&old_w_dollar, "$");
	str_append(&old_w_dollar, old);
	free(old);
	value = ft_strdup(hash_search(context->env, "HOME_BKP", SET));
	new = reshape_string(old_w_dollar, "~", value, 0);
	free(value);
	return (new);
}

static void	evaluate_dollar(t_list **curr, char *dol, t_data *context)
{	
	char	*var;
	char	*content;

	var = NULL;
	content = (*curr)->content;
	if ((ft_strlen(content) == 1)
		|| (*(dol + 1) == '\0')
		|| (*(dol + 1) == ' ')
		|| (*(dol + 1) == '\'' || *(dol + 1) == '\"'))
		*curr = (*curr)->next;
	else if (ft_isdigit(*(dol + 1)))
	{
		append_char(&var, *(dol + 1));
		(*curr)->content = reshape_string(content, var, NULL, dol - content);
		free(var);
	}
	else
		(*curr)->content = expand_variable(content, context);
}

/*
Expands variables (if any) on a given token
*/
t_list	*expand_token(t_list *tokens, t_data *context)
{
	t_list	*current;
	char	*dollar;

	current = tokens;
	while (current)
	{
		if ((current->prev && !ft_strcmp("<<", current->prev->content))
			|| is_quote_token(current, '\''))
		{
			current = current->next;
			continue ;
		}
		if (ft_strchr(current->content, '~'))
			current->content = expand_tilde(current->content, context);
		dollar = ft_strchr(current->content, '$');
		if (dollar)
		{
			evaluate_dollar(&current, dollar, context);
			continue ;
		}
		current = current->next;
	}
	return (tokens);
}

