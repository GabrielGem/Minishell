/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 09:58:31 by mmaquine          #+#    #+#             */
/*   Updated: 2025/12/22 11:27:40 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	line = readline("$> ");
	while (line)
	{
		build_tree(line);
		free(line);
		line = readline("$> ");
	}
}
