/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 00:19:03 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/30 07:37:49 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/ioctl.h>

#include "ft_select.h"
#include "termcap_macros.h"

/*
** Output to stout
*/
void	print_list(t_select *select)
{
	t_list	*l;
	int		fd;

	fd = 1;
	l = select->selected;
	while (l)
	{
		ft_dprintf(fd, "%s", (char *)l->content);
		l = l->next;
		if (l)
			write(fd, " ", 1);
	}
}

void	clear(t_select *select)
{
	//int				printed_lines;
	//int				fd;
	//struct winsize	ws;

	//fd = ((t_termios *)termios_if(&termios_get))->fd;
	//ioctl(fd, TIOCGWINSZ, &ws);
	//printed_lines = select->wcount / ws.ws_col;
	//get_cursor_position(&select->cursor_x, &select->cursor_y);
	//select->cursor_y -= printed_lines;
	get_cursor_position(&select->cursor_x, &select->cursor_y);
	TERM_GOTO(&ft_put, 0, select->cursor_y - select->num_row);
	TERM_CLEAR_DOWN(&ft_put);
}

void	refresh(t_select *sel)
{
	static t_select		*select = NULL;

	if (!select)
		select = sel;
	clear(select);
	display_list(select);
}

static int		is_selected(t_select *select, char *el)
{
	t_list	*l;

	l = select->selected;
	while (l)
	{
		if (ft_strequ(el, (char *)l->content))
			return (1);
		l = l->next;
	}
	return (0);
}

void	select_element(t_select *select)
{
	char	*el;
	t_list	*l;
	int		idx;

	idx = select->cursor_idx;
	if (idx < 0 || idx > select->nb_elem)
		return ;
	el = select->list[idx];
	if (!is_selected(select, el))
	{
		l = ft_lstnew(el, ft_strlen(el) + 1);
		ft_lstadd(&select->selected, l);
		move_next_col(select);
		refresh(select);
	}
}

void	remove_element(t_select *select)
{
	char	*el;
	t_list	*l;
	t_list	*l_prev;
	int		idx;

	idx = select->cursor_idx;
	if (idx < 0 || idx > select->nb_elem)
		return ;
	el = select->list[select->cursor_idx];
	if (is_selected(select, el))
	{
		l = select->selected;
		l_prev = l;
		while (l)
		{
			if (ft_strequ(el, (char *)l->content))
			{
				if (l == l_prev)
					select->selected = l->next;
				else
					l_prev->next = l->next;
				ft_memdel((void *)&l->content);
				ft_memdel((void *)&l);
				refresh(select);
				break ;
			}
			l_prev = l;
			l = l->next;
		}
	}
}

void	display_list(t_select *select)
{
	char	**list;
	int		fd;
	int		i;
	int		selected;
	int		width;
	char	blank[512];
	struct winsize	ws;

	select->num_row = 0;

	ft_memset(&blank, ' ', 512);
	list = select->list;
	//fd = select->tty.fd;
	fd = ((t_termios *)termios_if(&termios_get))->fd;
	ioctl(fd, TIOCGWINSZ, &ws);
	select->col_width = (select->col_width < ws.ws_col - 2) ? select->col_width : ws.ws_col - 2;
	//fd = 3;
	i = 0;
	select->wcount = 0;
	while (*list)
	{
		selected = is_selected(select, *list);
		//if (select->wcount + select->col_width > ws.ws_col)
		if (select->wcount > ws.ws_col)
		{
			TERM_CURSOR_DOWN(&ft_put);
			TERM_CURSOR_LINE_BEGIN(&ft_put);
			select->num_row += select->wcount / ws.ws_col;
			select->wcount = 0;
			//select->cursor_y--;
		}
		if (i == select->cursor_idx)
			TERM_UNDERLINE_START(&ft_put);
		if (selected)
			TERM_STANDOUT_START(&ft_put);
		width = ft_dprintf(fd, *list);
		select->wcount += width + select->col_width + 2;
		if (selected)
			TERM_STANDOUT_END(&ft_put);
		if (i == select->cursor_idx)
			TERM_UNDERLINE_END(&ft_put);
		list++;
		if (*list)
			write(fd, blank, select->col_width - width + 2);
			//select->wcount += write(fd, " ", 1);
		i++;
	}
}
