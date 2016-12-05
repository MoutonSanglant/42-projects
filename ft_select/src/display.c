/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 19:49:00 by tdefresn          #+#    #+#             */
/*   Updated: 2016/12/05 19:54:56 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>

#include "ft_select.h"
#include "termcap_macros.h"

void	clear(t_select *select)
{
	struct winsize	ws;
	int		row_size;
	int		fd;

	if (select->flags & FLAG_INLINE)
	{
		fd = ((t_termios *)termios_if(&termios_get))->fd;
		ioctl(fd, TIOCGWINSZ, &ws);
		row_size = ws.ws_col / select->col_width;
		get_cursor_position(&select->cursor_x, &select->cursor_y);
		if (row_size < select->row_size)
			select->cursor_y += (ws.ws_col / (select->row_size - 1)) * select->nb_elem / ws.ws_col + 1;
		//TERM_GOTO(&ft_put, 0, select->cursor_y - 1);
		char *s = ft_itoa(select->num_row);
		ft_putstr_fd("num_row: ", 2);
		ft_putendl_fd(s, 2);
		s = ft_itoa(select->cursor_y);
		ft_putstr_fd("y: ", 2);
		ft_putendl_fd(s, 2);
		TERM_GOTO(&ft_put, 0, select->cursor_y - select->num_row);
		TERM_CLEAR_DOWN(&ft_put);
	}
	else
	{
		TERM_CLEAR_ALL(&ft_put);
	}
}

void		refresh(t_select *select)
{
	static t_select		*s_select = NULL;

	if (!s_select)
		s_select = select;
	clear(s_select);
	display_list(s_select);
}

void	display_list(t_select *select)
{
	char	**list;
	int		fd;
	int		i;
	int		col;
	int		selected;
	int		width;
	//char	blank[512];
	struct winsize	ws;
	int		rows;

	//ft_memset(&blank, ' ', 512);
	list = select->list;
	fd = ((t_termios *)termios_if(&termios_get))->fd;
	ioctl(fd, TIOCGWINSZ, &ws);
	select->col_width = (select->col_width < ws.ws_col) ? select->col_width : ws.ws_col;
	select->row_size = ws.ws_col / select->col_width;
	// pre-check number of rows
	select->stop = 0;
	if (select->row_size == 1)
		rows = (ws.ws_col / 1) * select->nb_elem / ws.ws_col + 1;
	else
		rows = (ws.ws_col / (select->row_size - 1)) * select->nb_elem / ws.ws_col + 1;
			char *ss = ft_itoa(rows);
			ft_putstr_fd("ROWS: ", 2);
			ft_putendl_fd(ss, 2);
	if (rows >= ws.ws_row)
	{
		clear(select);
		ft_putstr_fd(MSG_SCREEN_TOO_SMALL, fd);
		select->stop = 1;
		return ;
	}
	select->row_size--;
	i = 0;
	col = 0;
	select->wcount = 0;
	select->num_row = 0;
	width = 0;
	while (*list)
	{
		selected = is_selected(select, *list);

		if (i == select->cursor_idx)
			TERM_UNDERLINE_START(&ft_put);
		if (selected)
			TERM_STANDOUT_START(&ft_put);

		width = print_element(fd, *list);
		if (selected)
			TERM_STANDOUT_END(&ft_put);
		if (i == select->cursor_idx)
			TERM_UNDERLINE_END(&ft_put);

		list++;
		if (*list)
		{
			int a = 0;
			TERM_CURSOR_RIGHT(&ft_put);
			while (a++ < select->col_width - width)
				TERM_CURSOR_RIGHT(&ft_put);
			//write(fd, blank, select->col_width - width);
		}
		i++;
		col++;
		if (col >= select->row_size)
		{
			col = 0;
			TERM_CURSOR_DOWN(&ft_put);
			TERM_CURSOR_LINE_BEGIN(&ft_put);
			select->wcount = 0;
			select->num_row += width / ws.ws_col + 1;
			char *s = ft_itoa(select->num_row);
			ft_putstr_fd("N: ", 2);
			ft_putendl_fd(s, 2);
		}
	}
}
/*
**	char *s = ft_itoa(ws.ws_col);
**	ft_putstr_fd("line width: ", 2);
**	ft_putendl_fd(s, 2);
**	s = ft_itoa(select->col_width);
**	ft_putstr_fd("col width: ", 2);
**	ft_putendl_fd(s, 2);
**	s = ft_itoa(select->row_size);
**	ft_putstr_fd("row size: ", 2);
**	ft_putendl_fd(s, 2);
*/
