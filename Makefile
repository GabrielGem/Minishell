# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gabrgarc <gabrgarc@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/23 14:33:20 by gabrgarc          #+#    #+#              #
#    Updated: 2026/01/19 10:55:49 by gabrgarc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = xaolins
CFLAGS = -Wall -Wextra -Werror -g3
INCLUDES = -I./includes -I./libft
LIBS = -Llibft -lft
RDFLAGS = -lreadline

MAIN_SRC = main.c

LEXER_SRCS = 

PARSER_SRCS = 

EXECUTOR_SRCS = \
	executor/executor.c \
	executor/handle_command.c \
	executor/handle_redirs.c

BUILTINS_SRCS =

UTILS_SRCS = \
	utils/binary_search.c \
	utils/concatenate.c \
	utils/is_valid_exec.c \
	utils/env/env_to_table.c \
	utils/env/table_to_env.c \
	utils/hashtable/hash.c \
	utils/hashtable/hash_item.c \
	utils/hashtable/hash_table.c \
	utils/hashtable/hash_upsert.c \
	utils/hashtable/hash_search.c \
	utils/hashtable/hash_delete.c \
	utils/hashtable/hash_destroy_item.c \
	utils/hashtable/hash_destroy_table.c

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
