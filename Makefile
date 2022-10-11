SRC	=	main.c	\

CFLAGS	=	-Wall -Wextra -Werror

CPPFLAGS	=	-I includes

OBJ	=	$(SRC:.c=.o)

NAME	=	bomberman

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) -lSDL2main -lSDL2

clean:
	rm -f	$(OBJ)

fclean:	clean
	rm	-f	$(NAME)

re:	fclean all
