ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

LONG_NAME	= libft_malloc_$(HOSTTYPE).so
NAME		= libft_malloc.so

CC		= gcc
LD		= ld
CFLAGS	= -Wall -Werror -Wextra -I./includes
#LDFLAGS	= --exclude-libs libc -L./libft -L.
LDFLAGS	=-L.
LDLIBS	=

# -pthreads (see `man gcc`)

SRC	= free malloc realloc show_alloc_mem \
		ft_bzero ft_strlen ft_putstr ft_putendl ft_putnbr

CORR_FILES = ./Makefile ./src ./includes

ifeq ($(BUILD), Bonus)
	CFLAGS	+= -D BONUS
	SRC		+=
endif

# DEBUG routine
ifeq ($(BUILD), Debug)
	CFLAGS	+= -fsanitize=address -g -O0 -D DEBUG
	SUFFIX	= .debug.o
	SRC		+=
else
	SUFFIX	= .o
endif

# OS flags
ARCH	= $(shell uname -m)
OS		= $(shell uname -s)

ifeq ($(OS), Darwin)
	LDLIBS +=
endif

ifeq ($(OS)_$(ARCH), Linux_x86_64)
	CFLAGS += -D LINUX
	LDLIBS += -lpthread
else ifeq ($(OS), Linux)
	CFLAGS += -D LINUX
	LDLIBS += -lpthread
endif

SRC_PREFIX = ./src/
OBJ_PREFIX = ./obj/

SRC := $(addsuffix .c, $(SRC))

OBJ = $(subst $(SRC_PREFIX), , $(SRC:.c=$(SUFFIX)))
OBJ := $(addprefix $(OBJ_PREFIX), $(OBJ))

.PHONY: all clean fclean re libft debug correction

all: $(NAME)

test: all
	@echo "making $@"
	$(MAKE) -C tests re

debug:
	@$(MAKE) BUILD=Debug all

#$(NAME): libft/libft.a $(OBJ)
$(NAME): $(OBJ)
	@echo "making $@"
	#$(CC) -shared -Wl,--whole-archive libft/libft.a -Wl,--no-whole-archive -o $(LONG_NAME) $^ $(CFLAGS) $(LDFLAGS) $(LDLIBS)
	$(CC) -shared -Wl,-soname,$(NAME) -o $(LONG_NAME) $^ $(CFLAGS) $(LDFLAGS) $(LDLIBS)
	@ln -s $(LONG_NAME) $(NAME)

$(OBJ_PREFIX)%$(SUFFIX): $(SRC_PREFIX)%.c
	@echo "making $<"
	@mkdir -p $(OBJ_PREFIX)
	@$(CC) -o $@ -c -fPIC $(CFLAGS) $<

clean:
	/bin/rm -rf $(OBJ_PREFIX)
	$(MAKE) -C libft clean

fclean: clean
	/bin/rm -f $(NAME)
	/bin/rm -f $(LONG_NAME)
	/bin/rm -rf $(TEST_PREFIX)
	$(MAKE) -C libft fclean

re: fclean all


libft/libft.a: libft

libft:
	@echo "making $@"
	@$(MAKE) -C libft BUILD=$(BUILD) -j 8

correction_%:
	@echo "\033[32mCopying $* into \033[33m/tmp/\033[0m"
	@mkdir -p /tmp/$*
	@mkdir -p /tmp/$*/includes
	@rsync -r --copy-links $(CORR_FILES) /tmp/$*
	@$(MAKE) -C libft correction_$*
	@$(MAKE) -C libftprintf correction_$*
