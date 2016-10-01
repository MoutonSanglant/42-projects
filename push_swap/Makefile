CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -I./includes
LDFLAGS	= -L./libft -L./libftprintf
LDLIBS	= -lft -lftprintf

ifeq ($(BUILD), Debug)
	CFLAGS	+= -fsanitize=address -g -O0 -D DEBUG
	SUFFIX	= .debug.o
	NAME	= push_swap.debug
else
	SUFFIX	= .o
	NAME	= push_swap
endif

ARCH	= $(shell uname -m)
OS		= $(shell uname -s)

ifeq ($(OS), Darwin)
	LDLIBS +=
endif

ifeq ($(OS)_$(ARCH), Linux_x86_64)
	CFLAGS += -D LINUX
	LDLIBS +=
else ifeq ($(OS), Linux)
	CFLAGS += -D LINUX
	LDLIBS +=
endif

SRC_PREFIX	= ./src/
OBJ_PREFIX	= ./obj/

SRC	=	main push swap rotate reverse_rotate print_swap error \
		basic_sort basic_sort_store basic_sort_insert

ifeq ($(BUILD), Debug)
	SRC +=
endif

SRC := $(addsuffix .c, $(SRC))
SRC := $(addprefix $(SRC_PREFIX), $(SRC))

OBJ = $(subst $(SRC_PREFIX), , $(SRC:.c=$(SUFFIX)))
OBJ := $(addprefix $(OBJ_PREFIX), $(OBJ))

.PHONY: all clean fclean re libft debug

all: $(NAME)

debug:
	@$(MAKE) BUILD=Debug all

$(NAME): $(OBJ) libft/libft.a
	@echo "making $@"
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS) $(LDLIBS)

libft/libft.a: libft

libft:
	@echo "making $@"
	@$(MAKE) -C libft BUILD=$(BUILD)

$(OBJ_PREFIX)%$(SUFFIX): $(SRC_PREFIX)%.c
	@echo "making $<"
	@mkdir -p $(OBJ_PREFIX)
	@$(CC) -o $@ -c $< $(CFLAGS)

clean:
	/bin/rm -rf $(OBJ_PREFIX)
	$(MAKE) -C libft clean

fclean: clean
	/bin/rm -f $(NAME)
	$(MAKE) -C libft fclean

cclean:
	/bin/rm -rf $(OBJ_PREFIX)
	/bin/rm -f $(NAME)

re: fclean all

rre: cclean all
