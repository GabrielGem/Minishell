# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmaquine <mmaquine@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/23 14:33:20 by gabrgarc          #+#    #+#              #
#    Updated: 2026/02/22 15:36:30 by gabrgarc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = xaolins
CFLAGS = -Wall -Wextra -Werror -g3
INCLUDES = -I./includes -I./libft
LIBS = -Llibft -lft
RDFLAGS = -lreadline

MAIN_SRC = main.c

LEXER_SRCS = \
	lexer/function.c\
	lexer/lexer_util.c\
	lexer/lexer_func.c\
	lexer/quote_util.c \
	lexer/quotes.c \
	lexer/remove_quotes.c \
	lexer/spaces.c \
	lexer/expander.c

PARSER_SRCS = \
	parser/parser_pipeline.c \
	parser/parser_util.c \
	parser/parsing.c

EXECUTOR_SRCS = \
	executor/executor.c \
	executor/wait_processes.c \
	executor/handle_command.c \
	executor/handle_pipe.c \
	executor/handle_redirs.c \
	executor/handle_fds.c \
	executor/heredoc/hunt_heredoc.c \
	executor/heredoc/handle_command_heredoc.c \
	executor/heredoc/handle_pipe_heredoc.c \
	executor/heredoc/heredoc.c

BUILTINS_SRCS = \
	builtins/cd.c \
	builtins/echo.c \
	builtins/env.c \
	builtins/exit.c \
	builtins/export.c \
	builtins/pwd.c \
	builtins/unset.c

UTILS_SRCS = \
	utils/get_prompt_string.c \
	utils/get_path.c \
	utils/binary_search.c \
	utils/concatenate.c \
	utils/is_valid_exec.c \
	utils/env_to_table.c \
	utils/table_to_envp.c \
	utils/table_for_array_of_items.c \
	utils/count_items_by_tag.c \
	utils/sort_array_of_items.c \
	utils/extract_key.c \
	utils/extract_value.c \
	utils/export_utils/get_sorted_export_items.c \
	utils/export_utils/is_valid_identifier.c \
	utils/export_utils/print_invalid_identifier.c \
	utils/free/free_tree.c \
	utils/free/free_shell.c \
	utils/hashtable/hash.c \
	utils/hashtable/hash_item.c \
	utils/hashtable/hash_table.c \
	utils/hashtable/hash_upsert.c \
	utils/hashtable/hash_update_tag.c \
	utils/hashtable/hash_search.c \
	utils/hashtable/hash_delete.c \
	utils/hashtable/hash_destroy_item.c \
	utils/hashtable/hash_destroy_table.c \
	utils/signal/signal_handler.c

TESTS_SRCS = \
	ft_test/print_functions.c \
	ft_test/build_tree_polimorphic.c

SRCS := $(MAIN_SRC) $(LEXER_SRCS) $(PARSER_SRCS) \
		$(EXECUTOR_SRCS) $(BUILTINS_SRCS) $(UTILS_SRCS)

SRCS := $(addprefix srcs/, $(SRCS))

OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
OBJS_DIRS = $(sort $(dir $(OBJS)))

DIR_LIBFT = ./libft
LIBFT = $(DIR_LIBFT)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS) $(RDFLAGS)

$(OBJS): | $(OBJS_DIR)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIRS)

$(OBJS_DIR)%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT): $(DIR_LIBFT)
	$(MAKE) -C $< all

val:
	@valgrind -q --leak-check=full --track-origins=yes \
	--track-fds=yes --show-leak-kinds=all \
	--suppressions=readline.supp ./$(NAME)

clean:
	$(MAKE) -C $(DIR_LIBFT) clean
	rm -rf $(OBJS_DIR)

fclean: clean
	$(MAKE) -C $(DIR_LIBFT) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
