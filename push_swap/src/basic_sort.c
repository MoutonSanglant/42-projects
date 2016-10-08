/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 19:06:54 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/05 02:40:05 by tdefresn         ###   ########.fr       */
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

static int	get_max(t_stack *stack)
{
	int		max;
	int		n;

	max = -2147483648;
	while (stack)
	{
		n = *(int *)stack->content;
		if (n > max)
			max = n;
		stack = stack->prev;
	}
	return (max);
}

static int	min_is_top_half(t_stack *stack, int min)
{
	int		halfsize;
	int		count;

	count = 0;
	halfsize = ft_stacksize(stack) / 2 + 1;
	while (count < halfsize)
	{
		if (*(int *)stack->content == min)
			return (1);
		stack = stack->prev;
		count++;
	}
	return (0);
}

void		basic_sort(t_swap *swap)
{
	char	*str;
	int		min;
	int		max;
	int		len;

	min = get_min(swap->a);
	max = get_max(swap->a);
	str = ft_strnew(1);
	str[0] = '\0';
	str = store_unsorted(swap, str, max);
	str = insert(swap, str);
	if (min_is_top_half(swap->a, min))
	{
		while (*(int *)swap->a->content != min)
			ft_asprintf(&str, "%s%s ", str, ra(swap));
	}
	else
	{
		while (*(int *)swap->a->content != min)
			ft_asprintf(&str, "%s%s ", str, rra(swap));
	}
	len = ft_strlen(str);
	str[(len >= 1) ? len - 1 : 0] = '\n';
	ft_printf(str);
	ft_strdel(&str);
}
