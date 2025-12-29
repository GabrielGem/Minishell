/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 10:11:10 by gabrgarc          #+#    #+#             */
/*   Updated: 2025/12/29 13:47:04 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
}	t_node_type;

typedef enum e_type_redir
{
	REDIN,
	REDOUT,
	APPEND,
	HEREDOC
}	t_type_redir;

typedef struct s_ast_node
{
	t_node_type			type;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	char				**param;
}	t_ast_node;

typedef struct s_redir
{
	t_type_redir	type;
	char			*filename;
	struct s_redir	*next;
}	t_redir;

typedef struct s_command
{
	int		is_builtin;
	char	**args;
	t_redir	*redirects;
}	t_command;

typedef struct s_data
{
	t_hash_table	*env;
	char			**envp;
	int				exit_status;
}	t_data;

typedef struct e_exec
{
	int	(*pipes)[2];
	int	*pids;
	int	cmd_count;
	int	stdin_backup;
	int	stdout_backup;
}	t_exec;

#endif
