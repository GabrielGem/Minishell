/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 17:12:00 by mmaquine          #+#    #+#             */
/*   Updated: 2026/02/24 22:20:33 by mmaquine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef enum e_quote_state
{
	NORMAL,
	IN_SINGLE_QUOTE,
	IN_DOUBLE_QUOTE
}	t_quote_state;

t_ast_node		*tree_build(char *line, t_data *context);
t_list			*tokenizer(char *line, t_data *context);
t_list			*remove_spaces(t_list *tokens);
t_list			*expand_token(t_list *tokens, t_data *context);
t_list			*initial_parser(char *line);

char			is_builtin(char *cmd);
void			remove_quotes(t_list *tokens);
char			*remove_quote_from_ends(char *old);
void			remove_param_quotes(t_list *tokens);
char			is_command_valid(t_list *tokens, t_data *context);
//lexer utils
void			print_tokens(t_list	*tokens);
void			str_append(char **str1, char *str2);
void			append_char(char **str1, char c);
int				check_spaces(char *line);
t_list			*add_tokens(char *content, char *token_found, char *token);
char			is_quote_token(t_list *token, char tkn);
char			is_single_or_double_quotes(t_list *token);
char			*extract_name(char	*token);
char			*expand_variable(char *token, t_data *context);
char			*expand_all_vars(char *old, t_data *context);
//parser utils
char			**list_to_array(t_list *list);
t_command		*parse_command(t_list **tokens);
char			is_redirect(char *token);
t_type_redir	get_redirect_type(char *token);
char			*remove_internal_quote(char *str);
#endif
