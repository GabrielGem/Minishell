/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 09:58:31 by mmaquine          #+#    #+#             */
/*   Updated: 2025/12/22 15:26:20 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*line;

	(void)argc;
	(void)argv;
	line = NULL;
	line = readline("$> ");
	while (line)
	{
		build_tree(line, env);
		free(line);
		line = readline("$> ");
	}
}
hello
