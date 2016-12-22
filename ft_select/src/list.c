/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 00:19:03 by tdefresn          #+#    #+#             */
/*   Updated: 2016/12/06 13:05:40 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int			print_element(int fd, char *el)
{
	char	*ext;
	int		wcount;
	int		color;

	if ((ext = ft_strchr(&el[1], '.')))
	{
		ext++;
		color = 0;
		while (*ext)
			color += *ext++;
		color %= 11;
		color++;
		if (color <= 6)
			color += 30;
		else if (color > 6)
			color = 90 + color - 6;
		ft_dprintf(fd, "\033[%im", color);
	}
	wcount = write(fd, el, ft_strlen(el));
	write(fd, "\033[0m", 4);
	return (wcount);
}

void		select_element(t_select *select)
{
	char	*el;
	int		idx;

	idx = select->cursor_idx;
	if (idx < 0 || idx >= select->nb_elem)
		return ;
	el = select->list[idx];
	if (!is_selected(select, el))
	{
		ft_lstadd(&select->selected, ft_lstnew(el, ft_strlen(el) + 1));
		refresh(select);
	}
	else
		remove_element(select);
	move_next_col(select);
}

static char	*get_el(t_select *select)
{
	int		idx;

	if (ft_lstsize(select->selected) < 1)
	{
		clear(select);
		quit();
	}
	idx = select->cursor_idx;
	if (idx < 0 || idx >= select->nb_elem)
		return (NULL);
	return (select->list[select->cursor_idx]);
}

void		remove_element(t_select *select)
{
	char	*el;
	t_list	*l;
	t_list	*l_prev;

	if ((el = get_el(select)) && is_selected(select, el))
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
