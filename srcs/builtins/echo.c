/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 11:43:36 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/16 17:23:40 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_echo(t_data *context, char **args)
{
	int	new_line_flag;

	(void)context;
	new_line_flag = 0;
	if (!ft_strncmp(args[1], "-n", 3))
	{
		new_line_flag = 1;
		args++;
	}
	args++;
	while (*args)
	{
		ft_putstr_fd(*args, STDOUT_FILENO);
		if (*(args + 1))
			ft_putstr_fd(" ", STDOUT_FILENO);
		args++;
	}
	if (!new_line_flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
