/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 09:58:31 by mmaquine          #+#    #+#             */
/*   Updated: 2026/01/20 21:15:40 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	main(int argc, char **argv, char **env)
{
	char	*line;

	(void)argc;
	(void)argv;
	(void)env;
	line = NULL;
	line = readline("$> ");
	while (line)
	{
		// tokenizer(line, env);
		if (check_quotes(line, '\"'))
		{
			char *c = ft_strrchr(line, '\"');
			*c = ' ';
		}
		printf("\t%s\n", line);
		free(line);
		line = readline("$> ");
	}
}
