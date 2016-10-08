/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_sort_store.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 21:10:39 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/05 02:43:24 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	issorted(t_stack *stack, int max)
{
	int		first;
	int		n1;
	int		n2;

	first = *(int *)stack->content;
	while (stack)
	{
		n1 = *(int *)stack->content;
		stack = stack->prev;
		if (stack)
			n2 = *(int *)stack->content;
		else
			n2 = first;
		if (n1 != max && n1 > n2)
			return (0);
	}
	return (1);
}

static int	isrevsorted(t_stack *stack, int max)
{
	int		first;
	int		n1;
	int		n2;

	first = *(int *)stack->content;
	while (stack)
	{
		n1 = *(int *)stack->content;
		stack = stack->prev;
		if (stack)
			n2 = *(int *)stack->content;
		else
			n2 = first;
		if (n2 != max && n1 < n2)
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

static int	store_init(t_swap *swap, char **str, int max)
{
	if (issorted(swap->a, max))
		return (1);
	if (isrevsorted(swap->a, max))
	{
		ft_asprintf(str, "%s%s ", *str, sa(swap));
		ft_asprintf(str, "%s%s ", *str, rra(swap));
	}
	if (*(int *)swap->a->content > *(int *)swap->a->prev->content)
		ft_asprintf(str, "%s%s ", *str, sa(swap));
	return (0);
}

char		*store_unsorted(t_swap *swap, char *str, int max)
{
	if (store_init(swap, &str, max))
		return (str);
	while (1)
	{
		if (issorted(swap->a, max))
			break ;
		if (get_unsorted_value(swap->a) > 0)
		{
			while (*(int *)swap->a->content == max ||
					*(int *)swap->a->content < *(int *)swap->a->prev->content)
				ft_asprintf(&str, "%s%s ", str, ra(swap));
			ft_asprintf(&str, "%s%s ", str, pb(swap));
		}
		else
		{
			while (*(int *)swap->a->content == max ||
					*(int *)swap->a->content < *(int *)swap->a->prev->content)
				ft_asprintf(&str, "%s%s ", str, rra(swap));
			ft_asprintf(&str, "%s%s ", str, pb(swap));
		}
		ft_printf(str);
		ft_strdel(&str);
		ft_strnew(1);
	}
	return (str);
}
