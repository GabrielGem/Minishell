/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 10:57:20 by mmaquine          #+#    #+#             */
/*   Updated: 2025/12/23 11:05:47 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	str_append(char **str1, char *str2)
{
	char	*append;

	append = ft_strjoin(*str1, str2);
	free(*str1);
	*str1 = append;
}