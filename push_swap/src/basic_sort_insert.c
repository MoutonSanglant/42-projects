/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_sort_insert.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 21:11:19 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/05 02:44:27 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
		if (n1 < n2 || (n1 > value && value > n2))
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

static int	get_last(t_stack *stack)
{
	int		last;

	last = 0;
	while (stack)
	{
		last = *(int *)stack->content;
		stack = stack->prev;
	}
	return (last);
}

static char	*roll(t_swap *swap, char *str)
{
	int		prev;

	prev = get_last(swap->a);
	while (*(int *)swap->a->content < *(int *)swap->b->content
			|| *(int *)swap->b->content < prev)
	{
		ft_asprintf(&str, "%s%s ", str, ra(swap));
		prev = get_last(swap->a);
	}
	ft_asprintf(&str, "%s%s ", str, pa(swap));
	return (str);
}

static char	*reverse_roll(t_swap *swap, char *str)
{
	int		prev;

	prev = get_last(swap->a);
	while (*(int *)swap->a->content < *(int *)swap->b->content
			|| *(int *)swap->b->content < prev)
	{
		ft_asprintf(&str, "%s%s ", str, rra(swap));
		prev = get_last(swap->a);
	}
	ft_asprintf(&str, "%s%s ", str, pa(swap));
	return (str);
}

char	*insert(t_swap *swap, char *str)
{
	while (1)
	{
		if (!swap->b || ft_stacksize(swap->b) < 1)
			break ;
		if (get_closest_sibling(swap->a, *(int *)swap->b->content))
			roll(swap, str);
		else
			str = reverse_roll(swap, str);
		ft_printf(str);
		ft_strdel(&str);
		ft_strnew(1);
	}
	return (str);
}
