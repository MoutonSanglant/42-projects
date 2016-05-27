/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 19:06:54 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/27 19:08:26 by tdefresn         ###   ########.fr       */
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

static int	get_closest_sibling(t_stack *stack, int value)
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
		if (n1 > value && value > n2)
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

void	basic_sort(t_swap *swap)
{
	//int			sorted;
	int			min;
	//int		n;

	min = get_min(swap->a);
	//sorted = 0;
	while (1)
	{
		//if ((!swap->b || ft_stacksize(swap->b) < 1) && issorted(swap->a))
		if (issorted(swap->a))
			break;

		// > 0 means top gap is smaller
		if (get_unsorted_value(swap->a) > 0)
		{
			while (*(int *)swap->a->content < *(int *)swap->a->prev->content)
			{
				//if ()
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
			rr(swap);i
		if (ft_stacksize(swap->a) < 2)
			break ;
*/

		//rr(swap);
		//if (*((int *)swap->a->content) == 6)
		//	break ;
		//_print_swap(swap);
	}
	ft_printf("\n========= SWAP STATE ==========\n");
	print_swap(swap);
	ft_printf("===============================\n");
	ft_printf("\nStep 2\n");
	while (1)
	{
		//ft_printf("B size: %i\n", ft_stacksize(swap->b));
		//if ((!swap->b || ft_stacksize(swap->b) < 1) && issorted(swap->a))
		if (!swap->b || ft_stacksize(swap->b) < 1)
			break ;

		if (get_closest_sibling(swap->a, *(int *)swap->b->content))
		{
			while (*(int *)swap->a->content < *(int *)swap->b->content)
			{
				ra(swap);
				ft_putchar(' ');
			}
			pa(swap);
	//ft_printf("\n========= SWAP STATE ==========\n");
	//print_swap(swap);
	//ft_printf("===============================\n");
		}
		else
		{
			while (*(int *)swap->a->content < *(int *)swap->b->content)
			{
				rra(swap);
				ft_putchar(' ');
			}
			pa(swap);
		}
		ft_putchar(' ');
	}
	while (*(int *)swap->a->content != min)
	{
		ra(swap);
		ft_putchar(' ');
	}
	ft_printf("\n========= SWAP STATE ==========\n");
	print_swap(swap);
	ft_printf("===============================\n");
}
