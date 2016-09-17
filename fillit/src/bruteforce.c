/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bruteforce.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/18 20:48:20 by tdefresn          #+#    #+#             */
/*   Updated: 2016/09/17 23:01:03 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

#define OVERLAP(a, b) (a & b) != 0

/*
** Check wether a position is valid or no
** Return 1 when out of bound
** Return 0 when valid
*/
static int	valid_position(t_bf_params *p, size_t grid_size,
							t_tetrimino *tetri, t_tetri_masks *tetri_masks)
{
	tetri_masks->last = tetri_masks->shifted >> grid_size;
	if (OVERLAP(p->grid->bottom, tetri_masks->last)
			&& OVERLAP(p->grid->bottom, tetri_masks->shifted))
	{
		tetri->h_shift = 0;
		tetri->v_shift = 0;
		return (1);
	}
	else if (tetri_masks->shift % grid_size)
	{
		tetri_masks->last = tetri_masks->shifted >> 1;
		if (OVERLAP(p->grid->right, tetri_masks->last)
				&& OVERLAP(p->grid->right, tetri_masks->shifted))
		{
			tetri->h_shift = 0;
			tetri->v_shift++;
			return (1);
		}
	}
	p->list->content = ft_memcpy(p->list->content, &tetri_masks->shifted,
									sizeof(t_mask64));
	tetri->h_shift++;
	return (0);
}

/*
** Find next valid position
** return 0 when end of grid is reached
*/
static int	overlap_test(t_bf_params *p, size_t grid_size,
							t_tetrimino *tetri, t_tetri_masks *tetri_masks)
{
	while (1)
	{
		tetri_masks->shift = grid_size * tetri->v_shift + tetri->h_shift;
		tetri_masks->shifted = tetri_masks->tetri << tetri_masks->shift;
		if (tetri_masks->shifted > p->grid->fill)
		{
			tetri->h_shift = 0;
			tetri->v_shift = 0;
			return (1);
		}
		if (OVERLAP(p->grid->tetri, tetri_masks->shifted))
			tetri->h_shift++;
		else if (!valid_position(p, grid_size, tetri, tetri_masks))
			break ;
	}
	return (0);
}

/*
** Bruteforce the result using backtracking
** Init test parameters then loop through
** positions
** return 0 on error:
**  - bitmask (> 64-bit)
**  - end of grid is reached
** exit loop and return actual grid when
** last tetri is reached
*/
t_mask64	bruteforce(t_bf_params *p, size_t grid_size,
						t_list *lst, t_mask64 current_tetrimino_mask)
{
	t_list			*previous_list;
	t_tetrimino		*tetrimino;

	if (!(p->list->content = ft_memalloc(sizeof(t_mask64))))
		memory_error();
	p->list->content_size = sizeof(t_mask64);
	tetrimino = (t_tetrimino *)lst->content;
	while (1)
	{
		p->grid->tetri = current_tetrimino_mask;
		if (overlap_test(p, grid_size, tetrimino, &tetrimino->mask))
			return (0);
		p->grid->tetri |= tetrimino->mask.shifted;
		if (!lst->next)
			break ;
		previous_list = p->list;
		if (!(p->list->next = ft_lstnew(NULL, 0)))
			memory_error();
		p->list = p->list->next;
		if ((p->grid->tetri = bruteforce(p, grid_size, lst->next, p->grid->tetri)))
			break ;
		p->list = previous_list;
		ft_lstdel(&p->list->next, &delelem);
	}
	return (p->grid->tetri);
}
