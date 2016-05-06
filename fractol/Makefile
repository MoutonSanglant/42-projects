CC		= gcc
CFLAGS	= -g -O0 -fsanitize=address -Wall -Werror -Wextra -I./libft -D BONUS
LDFLAGS	= -L./lib -L./libft
LDLIBS	= -lft -lm

ifeq ($(BUILD), Debug)
CFLAGS	+= -g -O0 -D DEBUG
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

SRC	=	main \
		alloc_error \
		new_mlx_sess \
		init_mlx_sess \
		start_mlx_sess \
		destroy_mlx_sess \
		draw_loop \
		draw_square \
		draw_image \
		draw_gui \
		draw_koch \
		clear_canvas \
		set_image_pixel \
		keydown \
		keypress \
		expose \
		bresenham_draw_line \
		draw_3dgrid \
		init_grid \
		init_grid_from_vertmap \
		matrix \
		matrix_math \
		rasterize \
		camera \
		inverse_matrix \
		projection_matrix \
		identity_matrix \
		change_grid_z \
		set_color_scheme \
		hex_to_float

ifeq ($(BUILD), Debug)
SRC += draw_debug_gui
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

re: fclean all
