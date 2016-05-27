/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_sort_store.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 21:10:39 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/27 22:16:24 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	issorted(t_stack *stack, int max)
{
	int		n1;
	int		n2;

	while (stack->prev)
	{
		n1 = *(int *)stack->content;
		stack = stack->prev;
		n2 = *(int *)stack->content;
		ft_printf("%i.%i;", n1, n2);
		if (n1 != max && n1 > n2)
			return (0);
	}
		ft_putchar('\n');
	return (1);
}

static int	get_unsorted_value(t_stack *stack, int min)
{
	int		bot_gap;
	int		top_gap;
	int		gap;
	int		n1;
	int		n2;

	(void)min;
	gap = 0;
	top_gap = -1;
	while (stack->prev)
	{
		n1 = *(int *)stack->content;
		stack = stack->prev;
		n2 = *(int *)stack->content;
		//if (n2 != min && n1 > n2)
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

char		*store_unsorted(t_swap *swap, char *str, int min, int max)
{
	while (1)
	{
		if (issorted(swap->a, max))
			break;
		if (get_unsorted_value(swap->a, min) > 0)
		{
			while (*(int *)swap->a->content == max ||
					*(int *)swap->a->content < *(int *)swap->a->prev->content)
				str = ft_sprintf("%s%s ", str, ra(swap));
			str = ft_sprintf("%s%s ", str, pb(swap));
		}
		else
		{
			while (*(int *)swap->a->content == max ||
					*(int *)swap->a->content < *(int *)swap->a->prev->content)
				str = ft_sprintf("%s%s ", str, rra(swap));
			str = ft_sprintf("%s%s ", str, pb(swap));
		}
	}
	ft_printf("\n========= STORE END ==========\n");
	print_swap(swap);
	ft_printf("================================\n");
	return (str);
}
