/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 01:41:45 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/10 01:48:26 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
**	Swap *
*/
static t_stack		*swap (t_stack *top)
{
	t_stack		*prev;

	if (!top || !top->prev)
		return (top);
	prev = top->prev;
	top->prev = prev->prev;
	prev->prev = top;
	return (prev);
}

void			sa (t_swap *s)
{
	ft_putstr("sa");
	s->a = swap(s->a);
}

void			sb (t_swap *s)
{
	ft_putstr("sb");
	s->b = swap(s->b);
}

void		ss (t_swap *s)
{
	ft_putstr("ss");
	s->a = swap(s->a);
	s->b = swap(s->b);
}
