/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 21:02:39 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/27 23:44:55 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	isint(char *str)
{
	if (str[0] == '-')
		str++;
	return (ft_isdigit(str[0]) && ft_strlen(str) < 11);
}

static void	push_to_a(int *n, t_swap *swap)
{
	t_stack	*stack;

	stack = swap->a;
	while (stack)
	{
		if (*n == *((int *)stack->content))
			error();
		stack = stack->prev;
	}
	stack = ft_stacknew((void *)n, sizeof(int));
	ft_stackpush(&swap->a, stack);
	ft_memdel((void **)&n);
}

void		init_swap(int argc, char **argv, t_swap *swap)
{
	int			*n;
	intmax_t	m;
	int			i;

	swap->a = NULL;
	swap->b = NULL;
	i = argc - 1;
	while (i > 0)
	{
		if (isint(argv[i]))
		{
			n = ft_memalloc(sizeof(int));
			m = ft_atoimax(argv[i]);
			if ((argv[i][0] == '-' && m < -2147483648) || m > 2147483647)
				error();
			*n = m;
		}
		else
			error();
		push_to_a(n, swap);
		i--;
	}
}

int			main(int argc, char **argv)
{
	t_swap		swap;

	if (argc < 2)
		return (0);
	init_swap(argc, argv, &swap);
	basic_sort(&swap);
	return (0);
}
