CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -I./includes
LDFLAGS	= -L./libft -L./libftprintf
LDLIBS	= -lft -lftprintf

SRC	=	main arguments options threads errors

CORR_FILES = ./Makefile ./src ./includes

ifeq ($(BUILD), Bonus)
	CFLAGS	+= -D BONUS
	SRC		+=
endif

# DEBUG routine
ifeq ($(BUILD), Debug)
	CFLAGS	+= -fsanitize=address -g -O0 -D DEBUG
	SUFFIX	= .debug.o
	NAME	= philo.debug
	SRC		+=
else
	SUFFIX	= .o
	NAME	= philo
endif

# OS flags
ARCH	= $(shell uname -m)
OS		= $(shell uname -s)

ifeq ($(OS), Darwin)
	LDLIBS +=
endif

ifeq ($(OS)_$(ARCH), Linux_x86_64)
	CFLAGS += -D LINUX
	LDLIBS += -pthread
else ifeq ($(OS), Linux)
	CFLAGS += -D LINUX
	LDLIBS += -pthread
endif

SRC_PREFIX = ./src/
OBJ_PREFIX = ./obj/

SRC := $(addsuffix .c, $(SRC))

OBJ = $(subst $(SRC_PREFIX), , $(SRC:.c=$(SUFFIX)))
OBJ := $(addprefix $(OBJ_PREFIX), $(OBJ))

.PHONY: all clean fclean re libft libftprintf debug correction

all: $(NAME)

debug:
	@$(MAKE) BUILD=Debug all

$(NAME): $(OBJ) libft/libft.a libftprintf/libftprintf.a
	@echo "making $@"
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS) $(LDLIBS)

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

cclean:
	/bin/rm -rf $(OBJ_PREFIX)
	/bin/rm -f $(NAME)

re: fclean all

rre: cclean all


libft/libft.a: libft

libft:
	@echo "making $@"
	@$(MAKE) -C libft BUILD=$(BUILD) -j 8

libftprintf/libftprintf.a: libftprintf

libftprintf:
	@echo "making $@"
	@$(MAKE) -C libftprintf BUILD=$(BUILD) -j 8

correction_%:
	@echo "\033[32mCopying $* into \033[33m/tmp/\033[0m"
	@mkdir -p /tmp/$*
	@mkdir -p /tmp/$*/includes
	@rsync -r --copy-links $(CORR_FILES) /tmp/$*
	@$(MAKE) -C libft correction_$*
	@$(MAKE) -C libftprintf correction_$*
