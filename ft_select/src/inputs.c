/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 22:07:41 by tdefresn          #+#    #+#             */
/*   Updated: 2016/12/05 17:46:42 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "ft_select.h"

#define KEY_RETURN	'\015'
#define KEY_ESC		'\033'
#define KEY_SIGTSTP	'\032'
#define KEY_SPACE	'\040'
#define KEY_BACKSPACE	'\177'
#define KEY_DELETE	('\033' | ('[' << 8) | ('3' << 16) | ('~' << 24))
#define KEY_UP		('\033' | ('[' << 8) | ('A' << 16))
#define KEY_DOWN	('\033' | ('[' << 8) | ('B' << 16))
#define KEY_RIGHT	('\033' | ('[' << 8) | ('C' << 16))
#define KEY_LEFT	('\033' | ('[' << 8) | ('D' << 16))


int		read_input()
{
	int		input;

	input = 0;
	if (read(0, &input, sizeof(int)) <= 0)
		return (0);
	return (input);
}

void	listen_input(t_select *select)
{
	int		input;

	while ((input = read_input()))
	{
		if (input == KEY_ESC)
		{
			clear(select);
			quit();
		}
		else if (input == KEY_RETURN)
			break ;
		if (select->stop)
			continue ;
		else if (input == KEY_UP)
			move_prev_row(select);
		else if (input == KEY_DOWN)
			move_next_row(select);
		else if (input == KEY_LEFT)
			move_prev_col(select);
		else if (input == KEY_RIGHT)
			move_next_col(select);
		else if (input == KEY_SPACE)
			select_element(select);
		else if (input == KEY_BACKSPACE || input == KEY_DELETE)
			remove_element(select);
	}
}
