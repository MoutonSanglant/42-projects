/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 16:06:21 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/27 20:51:34 by tdefresn         ###   ########.fr       */
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

char			*ra (t_swap *s)
{
	if (s->a)
		s->a = rotate (s->a);
	return ("ra");
}

char			*rb (t_swap *s)
{
	if (s->b)
		s->b = rotate (s->b);
	return ("rb");
}

char			*rr (t_swap *s)
{
	if (s->a)
		s->a = rotate (s->a);
	if (s->b)
		s->b = rotate (s->b);
	return ("rr");
}
