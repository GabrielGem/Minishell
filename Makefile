NAME = xaolins
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I./includes -I./libft
LIBS = -Llibft -lft
RDFLAGS = -lreadline

MAIN_SRC = main.c

LEXER_SRCS = 

PARSER_SRCS = \
	parser/function.c\
	parser/parser_util.c\
	parser/tree_func.c

EXECUTOR_SRCS = 

BUILTINS_SRCS =

UTILS_SRCS = \
# 	utils/env/binary_search.c \
# 	utils/env/concatenate.c \
# 	utils/env/env_to_table.c \
# 	utils/env/table_to_env.c \
# 	utils/env/is_valid_exec.c \
# 	utils/hashtable/hash.c \
# 	utils/hashtable/hash_item.c \
# 	utils/hashtable/hash_table.c \
# 	utils/hashtable/hash_upsert.c \
# 	utils/hashtable/hash_search.c \
# 	utils/hashtable/hash_delete.c \
# 	utils/hashtable/hash_destroy_item.c \
# 	utils/hashtable/hash_destroy_table.c

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