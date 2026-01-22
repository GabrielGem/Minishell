/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 09:58:31 by mmaquine          #+#    #+#             */
/*   Updated: 2026/01/22 16:54:08 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_list	*token;
	t_list	*new_list;
	t_list	*iterate;

	(void)argc;
	(void)argv;
	(void)env;
	line = NULL;
	line = readline("$> ");
	while (line)
	{
		token = ft_lstnew(line);
		new_list = evaluate_quotes(token, '\"');
		iterate = new_list;
		while (iterate)
		{
			printf("%s\n", (char *)(iterate->content));
			iterate = iterate->next;
		}
		ft_lstclear(&new_list, free);
		ft_lstdelone(token, free);
		line = readline("$> ");
	}
}
