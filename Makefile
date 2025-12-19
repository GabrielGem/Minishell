NAME = xaolins

SRC =	main.c\
		src/tree_func.c

OBJ =	$(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror -g

DIR_LIBFT = ./libft
LIBFT = $(DIR_LIBFT)/libft.a

LIBS = -lreadline

all : $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $^ $(LIBS) -o $@

$(LIBFT) : $(DIR_LIBFT)
	$(MAKE) -C $< all

clean:
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re: fclean all