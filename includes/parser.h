#ifndef PARSER_H
t_ast_node	*new_node(void);
t_ast_node	*build_tree(char *line, char **env);

int			is_builtin(char *cmd);
void	split_token(t_list *tokens, char *cmd);
//utils
void		str_append(char **str1, char *str2);
#endif