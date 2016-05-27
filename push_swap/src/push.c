/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 16:36:51 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/27 23:44:20 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
**	Push *
*/

char		*pa(t_swap *s)
{
	t_stack		*el;

	if (!s->b)
		return ("");
	el = ft_stackpop(&s->b);
	ft_stackpush(&s->a, el);
	return ("pa");
}

char		*pb(t_swap *s)
{
	t_stack		*el;

	if (!s->a)
		return ("");
	el = ft_stackpop(&s->a);
	ft_stackpush(&s->b, el);
	return ("pb");
}
