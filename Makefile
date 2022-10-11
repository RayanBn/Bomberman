SRC	=	main.c	\
		src/path.c	\
		src/env.c	\
		src/my_strcmp.c	\
		src/builtin.c	\
		src/my_strcpy.c	\
		src/handling.c	\
		src/my_strlen.c	\
		src/separators.c	\
		src/concat_str.c	\
		src/my_str_to_word_array.c	\

CFLAGS	=	-Wall -Wextra -g

CPPFLAGS	=	-I includes

OBJ	=	$(SRC:.c=.o)

NAME	=	mysh

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ)

clean:
	rm -f	$(OBJ)

fclean:	clean
	rm	-f	$(NAME)

re:	fclean all

.PHONY = all clean fclean re
