CC		= gcc
#CFLAGS	= -Wall -Werror -Wextra -I./includes
CFLAGS	= -Wall -Wextra -I./includes
LDFLAGS	= -L./libft -L./libftprintf
LDLIBS	= -lft -lftprintf

SRC		= main errors options \
			arguments input \
			matrix matrix_math identity_matrix inverse_matrix projection_matrix \
			glad
LIBS	= libft libftprintf
LIBS_A	= libft/libft.a libftprintf/libftprintf.a

CORR_FILES = ./Makefile ./src ./includes

ifeq ($(BUILD), Bonus)
	CFLAGS	+= -D BONUS
	SRC		+=
endif

# DEBUG routine
ifeq ($(BUILD), Debug)
	CFLAGS	+= -fsanitize=address -g -O0 -D DEBUG
	SUFFIX	= .debug.o
	NAME	= rtv1.debug
	SRC		+=
else
	SUFFIX	= .o
	NAME	= rtv1
endif

# OS flags
ARCH	= $(shell uname -m)
OS		= $(shell uname -s)

ifeq ($(OS), Darwin)
	LDFLAGS	+= -L./glfw3
	LDLIBS	+= -lglfw3 -framework Cocoa -framework OpenGL \
			-framework IOKit -framework CoreVideo
	LIBS	+= glfw3
	LIBS_A	+= glfw3/glfw3.a
endif

ifeq ($(OS)_$(ARCH), Linux_x86_64)
	CFLAGS	+= `pkg-config --cflags glfw3` -D LINUX
	LDFLAGS	+=
	LDLIBS	+= -lGLEW -lGL `pkg-config --static --libs glfw3`
else ifeq ($(OS), Linux)
	CFLAGS	+= `pkg-config --cflags glfw3` -D LINUX
	LDFLAGS	+=
	LDLIBS	+= `pkg-config --static --libs glfw3` -lGL
endif

SRC_PREFIX = ./src/
OBJ_PREFIX = ./obj/

SRC := $(addsuffix .c, $(SRC))

OBJ = $(subst $(SRC_PREFIX), , $(SRC:.c=$(SUFFIX)))
OBJ := $(addprefix $(OBJ_PREFIX), $(OBJ))

.PHONY: all clean fclean re libft libftprintf glfw3 debug correction

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
	$(foreach lib, $(LIBS), $(MAKE) -C $(lib) clean;)

fclean: clean
	/bin/rm -f $(NAME)
	$(foreach lib, $(LIBS), $(MAKE) -C $(lib) fclean;)

cclean:
	/bin/rm -rf $(OBJ_PREFIX)
	/bin/rm -f $(NAME)

re: fclean all

rre: cclean all

glfw3/glfw3.a: glfw3

glfw3:
	@echo "making $@"
	@$(MAKE) -C glfw3 BUILD=$(BUILD) -j 8


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
