CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -std=c99 --pedantic
LDFLAGS	=
LDLIBS	=

NAME	= common_test
SUFFIX	= .o

SRC_PREFIX	= ./src/
OBJ_PREFIX	= ./obj/

SRC	=	main \
		options \
		math/matrix math/matrix_math \
		math/matrix_inverse math/matrix_projection

SRC := $(addsuffix .c, $(SRC))

OBJ = $(subst $(SRC_PREFIX), , $(SRC:.c=$(SUFFIX)))
OBJ := $(addprefix $(OBJ_PREFIX), $(OBJ))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@echo "making $@"
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS) $(LDLIBS)

$(OBJ_PREFIX)%$(SUFFIX): $(SRC_PREFIX)%.c
	@echo "making $<"
	@mkdir -p $(OBJ_PREFIX)
	@mkdir -p $(OBJ_PREFIX)/math
	@$(CC) -o $@ -c $< $(CFLAGS)

clean:
	/bin/rm -rf $(OBJ_PREFIX)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
