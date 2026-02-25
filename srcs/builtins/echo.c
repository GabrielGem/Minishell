/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 11:43:36 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/24 15:33:43 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_echo(t_data *context, char **args)
{
	int	new_line_flag;

	(void)context;
	new_line_flag = 0;
	if (args[1] && !ft_strncmp(args[1], "-n", 3))
	{
		new_line_flag = 1;
		args++;
	}
	args++;
	while (*args)
	{
		ft_putstr_fd(*args, 1);
		if (*(args + 1))
			ft_putstr_fd(" ", 1);
		args++;
	}
	if (!new_line_flag)
		ft_putchar_fd('\n', 1);
	return (0);
}
