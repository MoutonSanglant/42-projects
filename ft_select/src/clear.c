/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 10:43:44 by tdefresn          #+#    #+#             */
/*   Updated: 2016/12/06 12:10:17 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>

#include "termcap_macros.h"
#include "ft_select.h"

void	clear(t_select *select)
{
	struct winsize	ws;
	int				row_size;
	int				fd;

	if (select->flags & FLAG_INLINE)
	{
		fd = ((t_termios *)termios_if(&termios_get))->fd;
		ioctl(fd, TIOCGWINSZ, &ws);
		row_size = ws.ws_col / select->col_width;
		get_cursor_position(&select->cursor_x, &select->cursor_y);
		if (row_size < select->row_size)
			select->cursor_y += (ws.ws_col / (select->row_size - 1))
				* select->nb_elem / ws.ws_col + 1;
		TERM_GOTO(&ft_put, 0, select->cursor_y - select->num_row);
		TERM_CLEAR_DOWN(&ft_put);
	}
	else
		TERM_CLEAR_ALL(&ft_put);
}
