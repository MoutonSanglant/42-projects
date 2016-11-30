/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 22:45:22 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/30 06:24:35 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	move_prev_row(t_select *select)
{
	select->cursor_idx = 0;
	refresh(select);
}

void	move_next_row(t_select *select)
{
	select->cursor_idx = 5;
	refresh(select);
}

void	move_prev_col(t_select *select)
{
	select->cursor_idx--;
	if (select->cursor_idx < 0)
		select->cursor_idx = select->nb_elem;
	refresh(select);
}

void	move_next_col(t_select *select)
{
	select->cursor_idx++;
	if (select->cursor_idx > select->nb_elem)
		select->cursor_idx = 0;
	refresh(select);
}
