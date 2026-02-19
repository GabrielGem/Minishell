#ifndef PARSER_H
# define PARSER_H

t_ast_node		*tree_build(char *line, t_data *context);
t_list			*tokenizer(char *line, t_data *context);
t_list			*remove_spaces(t_list *tokens);
t_list			*expand_token(t_list *tokens, t_data *context);

char			is_builtin(char *cmd);
void			*split_token(t_list *tokens, char *cmd, char *forbid);
//lexer utils
void			print_tokens(t_list	*tokens);
void			str_append(char **str1, char *str2);
int				check_spaces(char *line);
t_list			*add_tokens(char *content, char *token_found, char *token);
t_list			*resolve_quotes(t_list *tokens);
char			is_quote_token(t_list *token, char tkn);
void			insert_new_tokens(t_list **hd, t_list *lt, t_list *md,\
				t_list *rt);
char			*extract_name(char	*token);
char			*expand_variable(char *token, t_data *context);
//parser utils
char			**list_to_array(t_list *list);
t_command		*parse_command(t_list **tokens, t_data *context);
char			is_redirect(char *token);
t_type_redir	get_redirect_type(char *token);
#endif
