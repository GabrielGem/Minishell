/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fallback_mechanism.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 13:16:13 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/22 13:16:47 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fallback_update(t_data *context)
{
	char	*home;
	char	*username;

	home = hash_search(context->env, "HOME", ENV);
	if (home)
		hash_upsert(context->env, "HOME_BKP", home, SET);
	username = hash_search(context->env, "LOGNAME", ENV);
	if (username)
		hash_upsert(context->env, "LOGNAME_BKP", username, SET);
}
