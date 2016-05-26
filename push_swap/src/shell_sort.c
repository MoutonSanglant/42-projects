/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 21:03:38 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/26 22:08:07 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_min(t_stack *stack)
{
	int		min;
	int		n;

	min = 2147483647;
	while (stack)
	{
		n = *(int *)stack->content;
		if (n < min)
			min = n;
		stack = stack->prev;
	}
	return (min);
}

static int	issorted(t_stack *stack)
{
	int		n1;
	int		n2;

	while (stack->prev)
	{
		n1 = *(int *)stack->content;
		stack = stack->prev;
		n2 = *(int *)stack->content;
		if (n1 > n2)
			return (0);
	}
	return (1);
}

static int	get_unsorted_value(t_stack *stack)
{
	int		bot_gap;
	int		top_gap;
	int		gap;
	int		n1;
	int		n2;

	gap = 0;
	top_gap = -1;
	while (stack->prev)
	{
		n1 = *(int *)stack->content;
		stack = stack->prev;
		n2 = *(int *)stack->content;
		if (n1 > n2)
		{
			if (top_gap < 0)
				top_gap = gap;
			gap = -1;
		}
		gap++;
	}
	bot_gap = gap;
	return (bot_gap - top_gap);

}

void	shell_sort(t_swap *swap)
{
	int			sorted;
	int			min;
	//int		n;

	min = get_min(swap->a);
	sorted = 0;
	while (!sorted)
	{
		//if ((!swap->b || ft_stacksize(swap->b) < 1) && issorted(swap->a))
		if (issorted(swap->a))
			break;

		// > 0 means top gap is smaller
		if (get_unsorted_value(swap->a) > 0)
		{
			while (*(int *)swap->a->content < *(int *)swap->a->prev->content)
			{
				ra(swap);
				ft_putchar(' ');
			}
			pb(swap);
		}
		else
		{
			while (*(int *)swap->a->content < *(int *)swap->a->prev->content)
			{
				rra(swap);
				ft_putchar(' ');
			}
			pb(swap);
		}
		ft_putchar(' ');
/*
		if ( > *((int *)swap->a->prev->content))
			pb(swap);
		else
			rr(swap);
		if (ft_stacksize(swap->a) < 2)
			break ;
*/

		//rr(swap);
		//if (*((int *)swap->a->content) == 6)
		//	break ;
		//_print_swap(swap);
	}
}
