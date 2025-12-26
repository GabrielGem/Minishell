/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 10:42:47 by gabrgarc          #+#    #+#             */
/*   Updated: 2025/12/23 17:24:47 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **concatenate(char **strs, char *join)
{
	char	*temp;
	int		i;

	i = 0;
	while (strs[i])
	{
		temp = ft_strjoin(strs[i], join);
		free(strs[i]);
		strs[i] = temp;
		i++;
	}
	return (strs);
}
