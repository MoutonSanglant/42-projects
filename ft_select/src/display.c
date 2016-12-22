/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 19:49:00 by tdefresn          #+#    #+#             */
/*   Updated: 2016/12/06 12:10:31 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>

#include "termcap_macros.h"
#include "ft_select.h"

static int	count_rows(struct winsize *ws, char *el)
{
	int		rows;
	int		el_width;

	rows = ft_strlen(el) / ws->ws_col;
	el_width = ws->ws_col + 1;
	if (el_width >= ws->ws_col)
		rows += el_width / ws->ws_col;
	return (rows);
}

static int	win_overflow(t_select *select, struct winsize *ws)
{
	char	**list;
	int		rows;
	int		i;

	i = 0;
	rows = 0;
	list = select->list;
	while (*list)
	{
		if (select->row_size == 1)
			rows += count_rows(ws, *list);
		else if (++i >= select->row_size)
		{
			rows++;
			i = 0;
		}
		if (rows >= ws->ws_row)
			return (1);
		list++;
	}
	return (0);
}

static int	prepare(t_select *select, struct winsize *ws, int fd)
{
	ioctl(fd, TIOCGWINSZ, ws);
	select->stop = 0;
	if (select->col_width > ws->ws_col)
		select->col_width = ws->ws_col;
	select->row_size = ws->ws_col / select->col_width;
	if (win_overflow(select, ws))
	{
		clear(select);
		ft_putstr_fd(MSG_SCREEN_TOO_SMALL, fd);
		select->stop = 1;
		return (1);
	}
	select->num_row = 0;
	return (0);
}

static int	print_item(t_select *select, char *el, int i, int fd)
{
	int		selected;
	int		wcount;

	selected = is_selected(select, el);
	if (i == select->cursor_idx)
		TERM_UNDERLINE_START(&ft_put);
	if (selected)
		TERM_STANDOUT_START(&ft_put);
	wcount = print_element(fd, el);
	if (selected)
		TERM_STANDOUT_END(&ft_put);
	if (i == select->cursor_idx)
		TERM_UNDERLINE_END(&ft_put);
	return (wcount);
}

void		display_list(t_select *select, char **list)
{
	struct winsize	ws;
	int				width;
	int				col;
	int				fd;
	int				i;

	i = 0;
	col = 0;
	width = 0;
	fd = ((t_termios *)termios_if(&termios_get))->fd;
	if (prepare(select, &ws, fd))
		return ;
	while (*list)
	{
		width = print_item(select, *list, i++, fd);
		if (*(++list))
			push_cursor(select->col_width - width);
		if (++col >= select->row_size)
		{
			TERM_CURSOR_DOWN(&ft_put);
			TERM_CURSOR_LINE_BEGIN(&ft_put);
			select->num_row += width / ws.ws_col + 1;
			col = 0;
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
