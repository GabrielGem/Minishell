/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 16:15:30 by mmaquine          #+#    #+#             */
/*   Updated: 2026/02/21 16:17:28 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	is_single_or_double_quotes(t_list *token)
{
	return (is_quote_token(token, '\'')
		|| is_quote_token(token, '\"'));
}