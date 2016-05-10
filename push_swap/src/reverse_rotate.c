/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 16:15:45 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/10 17:11:57 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
**	Reverse Rotate *
*/
static t_stack		*rev_rotate (t_stack *top)
{
	t_stack		*el;
	t_stack		*last;

	el = top;
	while (el->prev)
	{
		last = el;
		el = el->prev;
	}
	el->prev = top;
	last->prev = NULL;
	return (el);
}

void			rra (t_swap *s)
{
	ft_putstr("rra");
	if (s->a)
		s->a = rev_rotate (s->a);
}

void			rrb (t_swap *s)
{
	ft_putstr("rrb");
	if (s->b)
		s->b = rev_rotate (s->b);
}

void			rrr (t_swap *s)
{
	ft_putstr("rrr");
	if (s->a)
		s->a = rev_rotate (s->a);
	if (s->b)
		s->b = rev_rotate (s->b);
}
