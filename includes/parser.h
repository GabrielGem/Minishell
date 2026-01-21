#ifndef PARSER_H
# define PRSER_H

t_ast_node	*new_node(void);
t_ast_node	*tokenizer(char *line, char **env);

int			is_builtin(char *cmd);
void		*split_token(t_list *tokens, char *cmd, char *forbid);
int			*tokenizer_quoting(t_list **tokens, char *line, int mode);
//utils
void		str_append(char **str1, char *str2);
int			check_spaces(char *line);
int			check_quotes(char *line, char quote);
#endif