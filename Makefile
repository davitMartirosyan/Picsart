NAME = text_editor
CC = gcc
CFLAGS= -I includes/ -std=c11 -pedantic -ggdb `pkg-config --cflags sdl2`
LIBS=`pkg-config --libs sdl2` -lm
INCLUDES = $(wildcard includes/*.h)
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBS)

%.o : %.c $(INCLUDES)
	$(CC) $(CFLAGS) $(LIBS) -c $< -o $@

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

.PHONNY: all fclean clean