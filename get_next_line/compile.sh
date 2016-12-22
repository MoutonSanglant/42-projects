gcc -g -O0 -fsanitize=address -std=c99 -Wall -Werror -Wextra main.c get_next_line.c -o gnl -L./libft -I./libft/src/ -lft
#./gnl testfile2
