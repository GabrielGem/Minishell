/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 09:58:31 by mmaquine          #+#    #+#             */
/*   Updated: 2026/01/26 14:26:54 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_list	*token;

	(void)argc;
	(void)argv;
	(void)env;
	line = NULL;
	line = readline("$> ");
	while (line)
	{
		token = ft_lstnew(line);
		evaluate_quotes(token, ft_strchr(token->content, '\"'));
		ft_lstdelone(token, free);
		line = readline("$> ");
	}
}
