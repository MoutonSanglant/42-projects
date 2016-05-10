/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 16:36:51 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/10 17:09:45 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
**	Push *
*/
void		pa (t_swap *s)
{
	t_stack		*el;

	ft_putstr("pa");
	if (!s->b)
		return ;
	el = ft_stackpop(&s->b);
	ft_stackpush(&s->a, el);
}

void		pb (t_swap *s)
{
	t_stack		*el;

	ft_putstr("pb");
	if (!s->b)
		return ;
	el = ft_stackpop(&s->a);
	ft_stackpush(&s->b, el);
}
