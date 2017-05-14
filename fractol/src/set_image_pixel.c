/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_image_pixel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 17:50:22 by tdefresn          #+#    #+#             */
/*   Updated: 2017/05/14 18:32:48 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
**	TODO
**	Manage different endians
**	(It should help to remove the void cast on 'mlx')
*/

void		set_image_pixel(t_context *ctx, t_image *img, int color,
							t_vec2ui32 *coord)
{
	int				opp;
	int				dec;
	unsigned char	*ptr;

	(void)ctx;
	opp = img->bpp * 0.125f;
	dec = opp;
	ptr = ((unsigned char *)img->data + coord->y * img->sl) + coord->x * opp;
	while (dec--)
		*(ptr + dec) = ((unsigned char *)(&color))[dec];
}
