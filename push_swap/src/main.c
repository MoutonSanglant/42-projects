/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 21:02:39 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/26 22:08:25 by tdefresn         ###   ########.fr       */
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

void	_print_swap(t_swap *swap)
{
	t_stack		*stack;

	ft_putchar('\n');
	ft_putendl("A | B");
	while (swap->a || swap->b)
	{
		if (swap->a)
		{
			ft_putnbr(*((int *)swap->a->content));
			stack = ft_stackpop(&swap->a);
			if (stack)
				ft_memdel((void **)&stack);
			else
				ft_memdel((void **)&swap->a);
		}
		else
		{
			ft_putchar('-');
		}
		ft_putstr(" | ");
		if (swap->b && ft_stacksize(swap->b))
		{
			ft_putnbr(*((int *)swap->b->content));
			stack = ft_stackpop(&swap->b);
			if (stack)
				ft_memdel((void **)&stack);
			else
				ft_memdel((void **)&swap->b);
		}
		ft_putchar('\n');
	}
}

int		main(int argc, char **argv)
{
	t_swap		swap;

	if (argc < 2)
		error();

	init_swap(argc, argv, &swap);
	shell_sort(&swap);
	_print_swap(&swap);

	return (0);
}
