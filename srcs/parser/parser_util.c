/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 19:25:01 by mmaquine          #+#    #+#             */
/*   Updated: 2026/02/13 17:01:26 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**list_to_array(t_list *list)
{
	char	**array;
	int		size;
	int		i;

	if (!list)
		return (NULL);
	size = ft_lstsize(list);
	array = ft_calloc(size + 1, sizeof(char *));
	if (!array)
		return (NULL);
	i = 0;
	while (list)
	{
		array[i] = ft_strdup(list->content);
		list = list->next;
		i++;
	}
	return (array);
}

/*
Check if a token is a redirect
*/
char	is_redirect(char *token)
{
	return (!ft_strcmp(">", token) 
		|| !ft_strcmp("<", token) 
		|| !ft_strcmp("<<", token)
		|| !ft_strcmp(">>", token));
}

/*
Return which redirects token represent
*/
t_type_redir	get_redirect_type(char *token)
{
	if (!ft_strcmp("<", token))
		return (REDIN);
	if (!ft_strcmp(">", token))
		return (REDOUT);
	if (!ft_strcmp("<<", token))
		return (HEREDOC);
	if (!ft_strcmp(">>", token))
		return (APPEND);
	return 0;
}
