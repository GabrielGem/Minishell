#ifndef PARSER_H
# define PARSER_H

typedef enum { NORMAL, IN_SINGLE_QUOTE, IN_DOUBLE_QUOTE} t_quote_state;

t_ast_node		*tree_build(char *line, t_data *context);
t_list			*tokenizer(char *line, t_data *context);
t_list			*remove_spaces(t_list *tokens);
t_list			*expand_token(t_list *tokens, t_data *context);
t_list			*initial_parser(char *line);

char			is_builtin(char *cmd);
void			*split_token(t_list *tokens, char *cmd, char *forbid);
void			remove_quotes(t_list *tokens);
char			*remove_quote(char *old);
//lexer utils
void			print_tokens(t_list	*tokens);
void			str_append(char **str1, char *str2);
void			append_char(char **str1, char c);
int				check_spaces(char *line);
t_list			*add_tokens(char *content, char *token_found, char *token);
t_list			*resolve_quotes(t_list *tokens);
char			is_quote_token(t_list *token, char tkn);
char			is_single_or_double_quotes(t_list *token);
void			insert_new_tokens(t_list **hd, t_list *lt, t_list *md,\
				t_list *rt);
char			*extract_name(char	*token);
char			*expand_variable(char *token, t_data *context);
char			*expand_all_vars(char *old, t_data *context);
//parser utils
char			**list_to_array(t_list *list);
t_command		*parse_command(t_list **tokens, t_data *context);
char			is_redirect(char *token);
t_type_redir	get_redirect_type(char *token);
#endif
