CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -I./includes
LDFLAGS	= -L./libft -L./libftprintf
LDLIBS	= -lft -lftprintf

CORR_FILES = ./Makefile ./src ./includes

ifeq ($(BUILD), Debug)
	CFLAGS	+= -g -O0 -D DEBUG
	SUFFIX	= .debug.o
	NAME	= ft_ls.debug
else
	SUFFIX	= .o
	NAME	= ft_ls
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

SRC	=	$(shell ls $(SRC_PREFIX)*.c)

ifeq ($(BUILD), Debug)
	SRC +=
endif

OBJ = $(subst $(SRC_PREFIX), , $(SRC:.c=$(SUFFIX)))
OBJ := $(addprefix $(OBJ_PREFIX), $(OBJ))

.PHONY: all clean fclean re libft libftprintf debug correction

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
	@$(CC) -o $@ -c $< $(CFLAGS)

clean:
	/bin/rm -rf $(OBJ_PREFIX)
	$(MAKE) -C libft clean
	$(MAKE) -C libftprintf clean

fclean: clean
	/bin/rm -f $(NAME)
	$(MAKE) -C libft fclean
	$(MAKE) -C libftprintf fclean

re: fclean all

correction_%:
	@echo "\033[32mCopying $* into \033[33m/tmp/\033[0m"
	@mkdir -p /tmp/$*
	@mkdir -p /tmp/$*/includes
	@rsync -r --copy-links $(CORR_FILES) /tmp/$*
	@$(MAKE) -C libft correction_$*
	@$(MAKE) -C libftprintf correction_$*
