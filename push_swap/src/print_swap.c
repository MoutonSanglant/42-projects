/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_swap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 17:39:00 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/27 18:46:29 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_swap(t_swap *swap)
{
	t_stack		*a;
	t_stack		*b;

	ft_putendl("A | B");
	a = swap->a;
	b = swap->b;
	while (a || b)
	{
		if (a)
		{
			ft_putnbr(*((int *)a->content));
			a = a->prev;
		}
		else
			ft_putchar('-');
		ft_putstr(" | ");
		if (b)
		{
			ft_putnbr(*((int *)b->content));
			b = b->prev;
		}
		else
			ft_putchar('-');
		ft_putchar('\n');
	}
}
