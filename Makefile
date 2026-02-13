NAME = xaolins
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I./includes -I./libft
LIBS = -Llibft -lft
RDFLAGS = -lreadline

MAIN_SRC = main.c

LEXER_SRCS = \
	lexer/function.c\
	lexer/lexer_util.c\
	lexer/lexer_func.c\
	lexer/quotes.c\
	lexer/spaces.c

PARSER_SRCS = \
	parser/parser_pipeline.c \
	parser/parser_util.c \
	parser/parsing.c \
	parser/tree_func.c

EXECUTOR_SRCS = \
	executor/handle_redirs.c

BUILTINS_SRCS =

UTILS_SRCS = \
	utils/free/free_tree.c \
	utils/free/free_shell.c \
	utils/env_to_table.c
# 	utils/binary_search.c \
# 	utils/concatenate.c \
# 	utils/is_valid_exec.c \
# 	utils/table_to_envp.c \
# 	utils/table_for_array_of_items.c \
# 	utils/count_items_by_tag.c \
# 	utils/sort_array_of_items.c \
# 	utils/extract_key.c \
# 	utils/extract_value.c \
# 	utils/export_utils/get_sorted_export_items.c \
# 	utils/export_utils/is_valid_identifier.c \
# 	utils/export_utils/print_invalid_identifier.c \
# 	utils/hashtable/hash.c \
# 	utils/hashtable/hash_item.c \
# 	utils/hashtable/hash_table.c \
# 	utils/hashtable/hash_upsert.c \
# 	utils/hashtable/hash_update_tag.c \
# 	utils/hashtable/hash_search.c \
# 	utils/hashtable/hash_delete.c \
# 	utils/hashtable/hash_destroy_item.c \
# 	utils/hashtable/hash_destroy_table.c

TESTS_SRCS = \
	ft_test/print_functions.c
# 	ft_test/build_tree_polimorphic.c

SRCS := $(MAIN_SRC) $(LEXER_SRCS) $(PARSER_SRCS) \
		$(EXECUTOR_SRCS) $(BUILTINS_SRCS) $(UTILS_SRCS)

SRCS := $(addprefix srcs/, $(SRCS))

OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

DIR_LIBFT = ./libft
LIBFT = $(DIR_LIBFT)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS) $(RDFLAGS)

$(OBJS_DIR)%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT): $(DIR_LIBFT)
	$(MAKE) -C $< all

clean:
	rm -rf $(OBJS_DIR)
	$(MAKE) -C $(DIR_LIBFT) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(DIR_LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re