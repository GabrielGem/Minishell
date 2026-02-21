/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 17:10:08 by mmaquine          #+#    #+#             */
/*   Updated: 2026/02/21 17:36:18 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*remove_quote(char *old)
{
	size_t	len;
	char	*new;

	if (!old)
		return (old);
	len = ft_strlen(old);
	new = ft_substr(old, 1, len - 2);
	free(old);
	return (new);
}

/*
Remove quotation marks from the ends.
*/
void	remove_quotes(t_list *tokens)
{
	while(tokens)
	{
		if (is_single_or_double_quotes(tokens))
			tokens->content = remove_quote(tokens->content);
		tokens = tokens->next;
	}
}
