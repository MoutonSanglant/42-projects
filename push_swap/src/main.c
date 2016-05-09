/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 21:02:39 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/10 01:49:03 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		pb (t_swap *s)
{
	t_stack		*el;

	ft_putstr("pb");
	//return ;
	//(*a)->prev = NULL;
	//(*b)->prev = NULL;
	el = ft_stackpop(&s->a);
	ft_stackpush(&s->b, el);
	//*a = (*a)->prev;
	//ft_stackpop(b);
}


int		main(int argc, char **argv)
{
	t_swap		swap;
	//t_stack		*a;
	//t_stack		*b;
	t_stack		*stack;
	int			*n;
	int			i;

	if (argc < 2)
		error();

	swap.a = NULL;
	swap.b = NULL;
	//a = ft_stacknew();
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
		ft_stackpush(&swap.a, stack);
		i--;
	}
	n = ft_memalloc((sizeof(int)));
	*n = 8;
	swap.b = ft_stacknew((void *)n, sizeof(int));
	//ft_stackpush(&b, stack);
	ft_memdel((void **)&n);
	/*while (a)
	{
		ft_putnbr(*((int *)a->content));
		ft_putchar('\n');
		ft_stackpop(&a);
	}*/
	ft_putchar('\n');
	sa(&swap);
	pb(&swap);
	ss(&swap);
	sb(&swap);
	sa(&swap);
	ft_putchar('\n');
	ft_putendl("A | B");
	while (swap.a)
	{
		ft_putnbr(*((int *)swap.a->content));
		ft_putstr(" | ");
		if (swap.b && ft_stacksize(swap.b))
		{
			ft_putnbr(*((int *)swap.b->content));
			stack = ft_stackpop(&swap.b);
			if (stack)
				ft_memdel((void **)&stack);
			else
				ft_memdel((void **)&swap.b);
		}
		ft_putchar('\n');
		stack = ft_stackpop(&swap.a);
		if (stack)
			ft_memdel((void **)&stack);
		else
			ft_memdel((void **)&swap.a);
	}

	return (0);
}
