#ifndef PARSER_H
# define PRSER_H

t_ast_node	*new_node(void);
t_ast_node	*tokenizer(char *line, char **env);

int			is_builtin(char *cmd);
void		*split_token(t_list *tokens, char *cmd, char *forbid);
//utils
void		str_append(char **str1, char *str2);
int			check_spaces(char *line);
int			check_quotes(char *line, char quote);
void		remove_quotes(t_list *tokens, char quote);
#endif