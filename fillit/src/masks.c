/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   masks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/17 22:07:33 by tdefresn          #+#    #+#             */
/*   Updated: 2016/09/17 22:21:59 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static t_mask64	ullpow(int b, int e)
{
	if (e > 0)
		return (b * ullpow(b, e - 1));
	else
		return (1);
}

static void		resize_masks(t_bf_params *p, size_t grid_size)
{
	size_t	i;

	p->grid->tetri = 0;
	p->grid->right = 0;
	p->grid->bottom = 0;
	p->grid->fill = 0;
	i = 0;
	while (++i <= grid_size)
		p->grid->right += ullpow(2, grid_size * i - 1);
	i = 0;
	while (i++ < grid_size )
		p->grid->bottom += ullpow(2, grid_size * grid_size - grid_size + i);
	i = 0;
	while (i < grid_size * grid_size)
		p->grid->fill += ullpow(2, i++);
}

/*
** Converts a 2-bytes pattern bitmask into a
** 8-bytes pattern bitmask, applying delta
*/
static void		convert(t_mask64 *mask, t_mask16 pattern_mask, int delta)
{
	size_t		bitshift;
	size_t		lineshift;

	bitshift = 0;
	lineshift = 0;
	if (delta > 0)
		while (bitshift < 16)
		{
			if (bitshift > 0 && bitshift % 4 == 0)
				lineshift += delta;
			*mask |= (pattern_mask & (1 << bitshift++)) << lineshift;
		}
	else
		while (bitshift < 16)
		{
			if (bitshift > 0 && bitshift % 4 == 0)
				lineshift -= delta;
			if (*mask & ((pattern_mask & (1 << bitshift)) >> lineshift))
			{
				*mask = 0;
				return ;
			}
			*mask |= (pattern_mask & (1 << bitshift++)) >> lineshift;
		}
}


static t_list	*clone(t_list *elem)
{
	void		*new_content;

	new_content = ft_memalloc(elem->content_size);
	ft_memcpy(new_content, elem->content, elem->content_size);
	return (ft_lstnew(new_content, elem->content_size));
}

/*
** may be missing (right after 'convert'):
** --------------------------
** if (!tetrimino->mask.tetri)
**		error();
** --------------------------
*/
t_list			*convert_list(t_bf_params *p, t_list *lst, size_t grid_size)
{
	t_list	*new_list;
	t_list	*p_list;
	t_tetrimino *tetrimino;

	resize_masks(p, grid_size);
	new_list = ft_lstmap(lst, clone);
	p_list = new_list;
	while (p_list)
	{
		tetrimino = (t_tetrimino *)p_list->content;
		tetrimino->mask.shifted = 0;
		tetrimino->mask.tetri = 0;
		convert(&tetrimino->mask.tetri, g_mask_table[(int)tetrimino->pattern_id][0], grid_size - 4);
		p_list = p_list->next;
	}
	return (new_list);
}
