/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 01:41:45 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/27 20:52:11 by tdefresn         ###   ########.fr       */
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

char			*sa (t_swap *s)
{
	s->a = swap(s->a);
	return ("sa");
}

char			*sb (t_swap *s)
{
	s->b = swap(s->b);
	return ("sb");
}

char			*ss (t_swap *s)
{
	s->a = swap(s->a);
	s->b = swap(s->b);
	return ("ss");
}
