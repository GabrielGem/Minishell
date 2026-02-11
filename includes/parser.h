#ifndef PARSER_H
# define PARSER_H

t_ast_node	*new_node(void);
t_ast_node	*tokenizer(char *line, char **env);
t_list		*remove_spaces(t_list *tokens);

int			is_builtin(char *cmd);
void		*split_token(t_list *tokens, char *cmd, char *forbid);
//utils
void		str_append(char **str1, char *str2);
int			check_spaces(char *line);
int			check_quotes(char *line, char quote);
t_list		*add_tokens(char *content, char *token_found, char *token);
t_list		*resolve_quotes(t_list *tokens);
char		is_quote_token(t_list *token, char tkn);
void		insert_new_tokens(t_list **hd, t_list *lt, t_list *md, t_list *rt);
char		is_redirect(char *token);
#endif