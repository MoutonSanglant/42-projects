/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 22:45:22 by tdefresn          #+#    #+#             */
/*   Updated: 2016/12/05 18:23:31 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	move_cursor(t_select *select, int count)
{
	select->cursor_idx += count;
	if (select->cursor_idx < 0)
		select->cursor_idx = select->nb_elem - 1;
	if (select->cursor_idx >= select->nb_elem)
		select->cursor_idx = 0;
	refresh(select);
}

void	move_prev_row(t_select *select)
{
	if (select->row_size < 2)
		move_cursor(select, -1);
	else
		move_cursor(select, -select->row_size);
}

void	move_next_row(t_select *select)
{
	if (select->row_size < 2)
		move_cursor(select, 1);
	else
		move_cursor(select, select->row_size);
}

void	move_prev_col(t_select *select)
{
	move_cursor(select, -1);
}

void	move_next_col(t_select *select)
{
	move_cursor(select, 1);
}
