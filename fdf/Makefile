CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -I./includes -D BONUS
LDFLAGS	= -L./lib -L./libft
LDLIBS	= -lft -lm

CORR_FILES = ./Makefile ./src ./lib ./includes

ifeq ($(BUILD), Debug)
CFLAGS	+= -g -O0 -fsanitize=address -D DEBUG
SUFFIX	= .debug.o
NAME	= fdf.debug
else
SUFFIX	= .o
NAME	= fdf
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

.PHONY: all clean fclean re libft debug correction

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
	@mkdir -p $(OBJ_PREFIX)debug/
	@$(CC) -o $@ -c $< $(CFLAGS)

clean:
	/bin/rm -rf $(OBJ_PREFIX)
	$(MAKE) -C libft clean

fclean: clean
	/bin/rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

correction_%:
	@echo "\033[32mCopying $* into \033[33m/tmp/\033[0m"
	@mkdir -p /tmp/$*
	@mkdir -p /tmp/$*/includes
	@rsync -r --copy-links $(CORR_FILES) /tmp/$*
	@$(MAKE) -C libft correction_$*
