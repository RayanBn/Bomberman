OBJ = $(SRC:.c=.o)

CFLAGS += -I./include
CFLAGS += -W -Werror -Wextra -Wall

LIBS += -lSDL2 -lSDL2_image -lSDL2 -lSDL2_ttf

all: $(NAME)

$(NAME): $(OBJ)
$(CC) $(OBJ) $(LIBS) -o $(NAME)

clean:
  rm -f $(OBJ)

fclean: clean
  rm -f $(NAME)
