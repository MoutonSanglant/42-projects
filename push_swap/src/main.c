/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 21:02:39 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/07 21:35:05 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		main(int argc, char **argv)
{
	t_stack		*a;
	t_stack		*b;
	t_stack		*stack;
	int			*n;
	int			i;

	if (argc < 2)
		error();

	a = NULL;
	b = NULL;
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
		ft_stackpush(&a, stack);
		i--;
	}
	while (a)
	{
		ft_putnbr(*((int *)a->content));
		ft_putchar('\n');
		ft_stackpop(&a);
	}
	return (0);
}
