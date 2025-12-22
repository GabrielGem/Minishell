/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_st.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 15:59:24 by mmaquine          #+#    #+#             */
/*   Updated: 2025/12/22 11:19:49 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_ST_H
# define MINISHELL_ST_H

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDDIR_IN,
	NODE_REDDIR_OUT,
	NODE_APPEND,
	NODE_HEREDOC,
	NODE_SEQUENCE
}	t_node_type;

typedef struct s_ast_node
{
	t_node_type			type;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	char				**param;
	t_list				*redirects;
}	t_ast_node;

#endif
