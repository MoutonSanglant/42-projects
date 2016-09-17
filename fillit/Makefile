NAME	= fillit

CC	= gcc
CFLAGS	= -Wall -Werror -Wextra -I./includes -g -O0
#-D DEBUG
#-fsanitize=address
LDFLAGS	= -L./lib -lft
LDLIBS	=

SRC_PREFIX = ./src/

SRC		= main list read_tetri_file get_tetriminos_from_buffer \
		masks fillit bruteforce print_grid errors

SRC := $(addsuffix .c, $(SRC))
SRC := $(addprefix $(SRC_PREFIX), $(SRC))

OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LDLIBS)

bin/%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	/bin/rm -f ${OBJ}

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
