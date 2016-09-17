/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/13 17:05:24 by tdefresn          #+#    #+#             */
/*   Updated: 2016/09/17 23:52:48 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int	biggest_square(int n)
{
	int	i;

	i = 1;
	while (i * i < n)
		i++;
	return (i);
}

static void	look_for_best_grid(t_bf_params *p, t_list *lst, size_t grid_size)
{
	t_list			*clone_lst;
	t_list			*start;
	t_mask64		grid;

	grid = 0;
	start = p->list;
	while (!grid)
	{
		if (grid_size > 8)
			grid_size_error();
		clone_lst = convert_list(p, lst, grid_size);
		grid = bruteforce(p, grid_size, clone_lst, p->grid->tetri);
		ft_lstdel(&clone_lst, &delelem);
		if (grid == 0)
		{
			ft_lstdel(&start, &delelem);
			start = ft_lstnew(NULL, 0);
			p->list = start;
			grid_size++;
		}
	}
	if (!(p->list = start))
		error();
	print_grid(grid_size, p->list);
}

/*
** lst: tetrimino list
*/
void	fillit(t_list *lst)
{
	t_bf_params		p;

	if (!lst)
		error();
	if (!(p.list = ft_lstnew(NULL, 0)))
		memory_error();
	if (!(p.grid = (t_grid_mask *)ft_memalloc(sizeof(t_grid_mask))))
		memory_error();
	look_for_best_grid(&p, lst, biggest_square(ft_lstsize(lst) * 4));
	ft_lstdel(&p.list, &delelem);
	ft_memdel((void **)&p.grid);
	ft_lstdel(&lst, &delelem);
}
