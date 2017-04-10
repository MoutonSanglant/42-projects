#LONG_NAME	= libft_malloc_$(HOSTTYPE).so
#NAME		= libft_malloc.so

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
LDFLAGS	= -L..
LDLIBS	=


TESTS = test1
PREFIX = tests/


.PHONY: all fclean re

all: $(TESTS)

$(TESTS):
	@echo "making $@"
	@mkdir -p $(PREFIX)
	@$(CC) -o $(PREFIX)$@ $@.c $(CFLAGS) $(LDFLAGS) $(LDLIBS) -lft_malloc

fclean:
	/bin/rm -rf $(PREFIX)

re: fclean all
