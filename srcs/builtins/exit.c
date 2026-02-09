/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 15:08:48 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/02/09 16:49:46 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	valid_argument(char *str);

int	b_exit(t_data *context, char **args)
{
	unsigned char	exit_code;

	exit_code = 0;
	printf("exit\n");
	if (args[1] && !valid_argument(args[1]))
	{
		dup2(context->stdout_backup, STDOUT_FILENO);
		printf("minishell: exit: %s: numeric argument required\n", args[1]);
		exit_code = 2;
	}
	else if (args[1] && args[2])
	{
		dup2(context->stdout_backup, STDOUT_FILENO);
		printf("minishell: exit: too many arguments\n");
		exit_code = 1;
	}
	else if (args[1])
		exit_code = ft_atoi(args[1]);
	free_shell(context);
	exit(exit_code);
}

static int	valid_argument(char *str)
{
	if (!str)
		return (1);
	if (*str == '+' || *str == '-')
		str++;
	if (!str)
		return (1);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}
