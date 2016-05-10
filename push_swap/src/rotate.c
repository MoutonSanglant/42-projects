/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 16:06:21 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/10 17:11:11 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
**	Rotate *
*/
static t_stack		*rotate (t_stack *top)
{
	t_stack *el;

	el = top;
	while (el->prev)
		el = el->prev;
	el->prev = top;
	if (top->prev)
		el = top->prev;
	top->prev = NULL;
	return (el);
}

void			ra (t_swap *s)
{
	ft_putstr("ra");
	if (s->a)
		s->a = rotate (s->a);
}

void			rb (t_swap *s)
{
	ft_putstr("rb");
	if (s->b)
		s->b = rotate (s->b);
}

void			rr (t_swap *s)
{
	ft_putstr("rr");
	if (s->a)
		s->a = rotate (s->a);
	if (s->b)
		s->b = rotate (s->b);
}
