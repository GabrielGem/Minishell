/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 14:13:31 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/01/30 14:17:21 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_key(char *line)
{
	char	*equal_sign;
	char	*key;
	int		key_len;

	if (!line)
		return (NULL);
	equal_sign = ft_strchr(line, '=');
	if (!equal_sign)
	{
		key = ft_strdup(line);
		return (key);
	}
	key_len = equal_sign - line;
	key = ft_substr(line, 0, key_len);
	return (key);
}
