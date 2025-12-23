/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 09:58:27 by mmaquine          #+#    #+#             */
/*   Updated: 2025/12/23 15:45:02 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "minishell_st.h"

t_ast_node	*new_node(void);
t_ast_node	*build_tree(char *line, char **env);

int			is_builtin(char *cmd);
char		*find_pipe(char *cmd);
//utils
void		str_append(char **str1, char *str2);
#endif
