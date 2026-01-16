/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 10:11:10 by gabrgarc          #+#    #+#             */
/*   Updated: 2026/01/15 17:23:49 by gabrgarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_type_redir
{
	REDIN,
	REDOUT,
	APPEND,
	HEREDOC
}	t_type_redir;

enum e_builtin
{
	STANDART,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
};

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
}	t_node_type;

typedef struct s_redir
{
	t_type_redir	type;
	char			*filename;
}	t_redir;

typedef struct s_node
{
	t_node_type	base;
}	t_node;

typedef struct s_ast_node
{
	t_node	type;
	t_node	*left;
	t_node	*right;
}	t_ast_node;

typedef struct s_command
{
	t_node	type;
	char	is_builtin;
	char	**args;
	t_list	*redirects;
}	t_command;

typedef struct e_exec
{
	t_node	type;
	int		**pipes;
	int		*pids;
	int		cmd_count;
	int		stdin_backup;
	int		stdout_backup;
}	t_exec;

typedef struct s_data
{
	t_hash_table	*env;
	char			**envp;
	t_ast_node		*root_node;
	int				exit_status;
}	t_data;

#endif
