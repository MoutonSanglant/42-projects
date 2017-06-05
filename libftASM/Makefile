CC		= nasm
CFLAGS	= -Wall -Werror -Wextra -I./includes
LDFLAGS	= -L./libft -L./libftprintf
LDLIBS	= -lft -lftprintf

SRC		=

CORR_FILES = ./Makefile ./src ./includes

ifeq ($(BUILD), Bonus)
	CFLAGS	+= -D BONUS
	SRC		+=
endif

# DEBUG routine
#
ifeq ($(BUILD), Debug)
	CFLAGS	+= -fsanitize=address -g -O0 -D DEBUG
	SUFFIX	= .debug.o
	NAME	= rtv1.debug
	SRC		+=
else
	SUFFIX	=
	NAME	= libfts.a
endif

# OS flags
ARCH	= $(shell uname -m)
OS		= $(shell uname -s)

ifeq ($(OS), Darwin)
	LDFLAGS	+=
	LDLIBS	+=
	LIBS	+=
endif

ifeq ($(OS)_$(ARCH), Linux_x86_64)
	CFLAGS	+=
	LDFLAGS	+=
	LDLIBS	+=
else ifeq ($(OS), Linux)
	CFLAGS	+=
	LDFLAGS	+=
	LDLIBS	+=
endif

SRC_PREFIX = ./src/
OBJ_PREFIX = ./obj/

SRC := $(addsuffix .c, $(SRC))

OBJ = $(subst $(SRC_PREFIX), , $(SRC:.c=$(SUFFIX)))
OBJ := $(addprefix $(OBJ_PREFIX), $(OBJ))

.PHONY: all clean fclean re debug correction

all: $(NAME)

debug:
	@$(MAKE) BUILD=Debug all

$(NAME): $(OBJ) $(LIBS_A)
	@echo "making $@"
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS) $(LDLIBS)

$(OBJ_PREFIX)%$(SUFFIX): $(SRC_PREFIX)%.c
	@echo "making $<"
	@mkdir -p $(OBJ_PREFIX)
	@$(CC) -o $@ -c $< $(CFLAGS)

clean:
	/bin/rm -rf $(OBJ_PREFIX)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

correction_%:
	@echo "\033[32mCopying $* into \033[33m/tmp/\033[0m"
	@mkdir -p /tmp/$*
	@mkdir -p /tmp/$*/includes
	@rsync -r --copy-links $(CORR_FILES) /tmp/$*
