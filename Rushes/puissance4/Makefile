# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdruel <gdruel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/10/10 15:46:02 by gdruel            #+#    #+#              #
#    Updated: 2016/02/27 18:35:00 by gdruel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = puissance4

SRC = main.c ai_play_turn.c score_map_fn.c grid_manager.c \
		vector2.c check_victory.c human_play_turn.c get_next_line.c
OBJ = main.o ai_play_turn.o score_map_fn.o grid_manager.o \
		vector2.o check_victory.o human_play_turn.o get_next_line.o

RM = rm -f

all: $(NAME)

$(NAME):
	make -C libft/
	gcc -Wall -Wextra -Werror -Ilibft/src -c $(SRC) -g -O0
	gcc -o $(NAME) $(OBJ) -Ilibft/src -Llibft/ -lft -g -O0

clean:
	make -C libft/ clean
	$(RM) $(OBJ)

fclean: clean
	make -C libft/ fclean
	$(RM) $(NAME)

re: fclean all
