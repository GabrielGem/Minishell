/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 14:44:52 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/09 15:04:02 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_unset(t_data *context, char **args)
{
	int	i;

	if (args[1] == NULL)
		return (0);
	i = 1;
	while (args[i])
	{
		if (hash_delete(context->env, args[i], ENV) == 1)
			hash_delete(context->env, args[i], EXPORT);
		i++;
	}
	return (0);
}
