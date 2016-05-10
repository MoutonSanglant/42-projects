/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 21:02:39 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/10 17:31:16 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	init_swap(int argc, char **argv, t_swap *swap)
{
	t_stack		*stack;
	int			*n;
	int			i;

	swap->a = NULL;
	swap->b = NULL;
	i = argc - 1;
	while (i > 0)
	{
		// Doesn't check if arg is not too big !!
		if (ft_isdigit(argv[i][0]))
		{
			n = ft_memalloc((sizeof(int)));
			*n = ft_atoi(argv[i]);
			stack = ft_stacknew((void *)n, sizeof(int));
			ft_memdel((void **)&n);
		}
		ft_stackpush(&swap->a, stack);
		i--;
	}
}

void	_print_swap(t_swap *swap)
{
	t_stack		*stack;

	ft_putchar('\n');
	ft_putendl("A | B");
	while (swap->a)
	{
		ft_putnbr(*((int *)swap->a->content));
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
		stack = ft_stackpop(&swap->a);
		if (stack)
			ft_memdel((void **)&stack);
		else
			ft_memdel((void **)&swap->a);
	}
}

void	sort_swap(t_swap *swap)
{
	int sorted;

	sorted = 0;
	while (!sorted)
	{
		rr(swap);
		if (*((int *)swap->a->content) == 6)
			break ;
		ft_putchar(' ');
		//_print_swap(swap);
	}
	//sa(&swap);
	//pa(&swap);
	//ss(&swap);
	//sb(&swap);
	//sa(&swap);
	//rr(swap);
	//rr(swap);
	//pa(&swap);
}

int		main(int argc, char **argv)
{
	t_swap		swap;

	if (argc < 2)
		error();

	init_swap(argc, argv, &swap);
	sort_swap(&swap);
	_print_swap(&swap);

	return (0);
}
