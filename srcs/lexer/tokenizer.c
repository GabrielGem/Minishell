/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 15:36:28 by mmaquine          #+#    #+#             */
/*   Updated: 2026/02/24 11:17:20 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	tokens = expand_token(tokens, context);
	remove_quotes(tokens);
	if (!is_command_valid(tokens, context))
	{
		ft_lstclear(&tokens, free);
		return (NULL);
	}
	return (tokens);
}
