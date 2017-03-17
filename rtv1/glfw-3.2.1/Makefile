NAME	= libglfw3.a

CC		= gcc
CFLAGS	= -D _GLFW_USE_CONFIG_H
LDFLAGS	=
LDLIBS	=

SUFFIX	= .o

SRC_PREFIX	= src/
OBJ_PREFIX	= obj/

#SRC_COCOA	=

C_SRC		= src/cocoa_time.c \
src/context.c \
src/init.c \
src/input.c \
src/monitor.c \
src/posix_tls.c \
src/window.c \
src/xkb_unicode.c
#src/vulkan.c \
#src/egl_context.c \
#src/glx_context.c \
#src/linux_joystick.c \
#src/mir_init.c \
#src/mir_monitor.c \
#src/mir_window.c \
#src/posix_time.c \
#src/wgl_context.c \
#src/win32_init.c \
#src/win32_joystick.c \
#src/win32_monitor.c \
#src/win32_time.c \
#src/win32_tls.c \
#src/win32_window.c \
#src/wl_init.c \
#src/wl_monitor.c \
#src/wl_window.c \
#src/x11_init.c \
#src/x11_monitor.c \
#src/x11_window.c \


OC_SRC = src/cocoa_init.m \
src/cocoa_joystick.m \
src/cocoa_monitor.m \
src/cocoa_window.m \
src/nsgl_context.m


C_OBJ		= $(subst $(SRC_PREFIX), , $(C_SRC:.c=$(SUFFIX)))
C_OBJ		:= $(addprefix $(OBJ_PREFIX), $(C_OBJ))
OC_OBJ		= $(subst $(SRC_PREFIX), , $(OC_SRC:.m=$(SUFFIX)))
OC_OBJ		:= $(addprefix $(OBJ_PREFIX), $(OC_OBJ))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(C_OBJ) $(OC_OBJ)
	@echo "making $@"
	@ar rc $@ $^
	@ranlib $(NAME)

$(OBJ_PREFIX)%$(SUFFIX): $(SRC_PREFIX)%.c
	@echo "making $@"
	@mkdir -p $(OBJ_PREFIX)
	@$(CC) -o $@ -c $< $(CFLAGS)

$(OBJ_PREFIX)%$(SUFFIX): $(SRC_PREFIX)%.m
	@echo "making $@"
	@mkdir -p $(OBJ_PREFIX)
	@$(CC) -o $@ -x objective-c -c $< $(CFLAGS)

clean:
	/bin/rm -f $(NAME)

fclean: clean
	/bin/rm -rf $(OBJ_PREFIX)

re: fclean all
