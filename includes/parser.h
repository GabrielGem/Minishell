#ifndef PARSER_H
# define PRSER_H

# define NORMAL_MODE		0
# define IN_DOUBLE_QUOTE	1
# define IN_SINGLE_QUOTE	2

t_ast_node	*new_node(void);
t_ast_node	*tokenizer(char *line, char **env);

int			is_builtin(char *cmd);
void		*split_token(t_list *tokens, char *cmd, char *forbid);
int			*tokenizer_quoting(t_list **tokens, char *line, int mode);
//utils
void		str_append(char **str1, char *str2);
int			check_spaces(char *line);
#endif