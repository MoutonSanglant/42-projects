CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -I./libft -I./includes
LDFLAGS	= -L./lib -L./libft -L./libftprintf
LDLIBS	= -lft -lftprintf -lm

ifeq ($(BUILD), Debug)
CFLAGS	+= -fsanitize=address -g -O0 -D DEBUG
SUFFIX	= .debug.o
NAME	= fractol.debug
else
SUFFIX	= .o
NAME	= fractol
endif

ARCH	= $(shell uname -m)
OS		= $(shell uname -s)

ifeq ($(OS), Darwin)
	LDLIBS += -lmlx -framework OpenGL -framework AppKit
endif

ifeq ($(OS)_$(ARCH), Linux_x86_64)
	CFLAGS += -D LINUX
	LDLIBS += -lX11 -lXext -lbsd -lmlx_linux_x64
else ifeq ($(OS), Linux)
	CFLAGS += -D LINUX
	LDLIBS += -lX11 -lXext -lbsd -lmlx_linux_x86
endif

SRC_PREFIX	= ./src/
OBJ_PREFIX	= ./obj/

SRC	=	$(shell ls $(SRC_PREFIX)*.c)

ifeq ($(BUILD), Debug)
	SRC	+= $(shell ls $(SRC_PREFIX)debug/*.c)
endif

OBJ = $(subst $(SRC_PREFIX), , $(SRC:.c=$(SUFFIX)))
OBJ := $(addprefix $(OBJ_PREFIX), $(OBJ))

.PHONY: all clean fclean re libft libftprintf debug

all: $(NAME)

debug:
	@$(MAKE) BUILD=Debug all

$(NAME): $(OBJ) libft/libft.a libftprintf/libftprintf.a
	@echo "making $@"
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS) $(LDLIBS)

libft/libft.a: libft

libftprintf/libftprintf.a: libftprintf

libft:
	@echo "making $@"
	@$(MAKE) -C libft BUILD=$(BUILD)

libftprintf:
	@echo "making $@"
	@$(MAKE) -C libftprintf BUILD=$(BUILD)

$(OBJ_PREFIX)%$(SUFFIX): $(SRC_PREFIX)%.c
	@echo "making $<"
	@mkdir -p $(OBJ_PREFIX)
	@mkdir -p $(OBJ_PREFIX)debug/
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
