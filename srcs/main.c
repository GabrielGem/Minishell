/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 09:58:31 by mmaquine          #+#    #+#             */
/*   Updated: 2026/01/27 20:56:16 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_list	*token;
	t_list	*iterate;

	(void)argc;
	(void)argv;
	(void)env;
	line = NULL;
	line = readline("$> ");
	while (line)
	{
		token = ft_lstnew(line);
		token = evaluate_quotes(token, ft_strchr(token->content, '\"'));
		iterate = token;
		while (iterate)
		{
			ft_printf("%s\n", (char *)(iterate->content));
			iterate = iterate->next;
		}
		ft_lstclear(&token, free);
		line = readline("$> ");
	}
}
 