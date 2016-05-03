/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_square.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 16:54:27 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/04 00:44:07 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	draw_square(t_mlx_st *mlx, int color, t_vec2f *from, t_vec2f *to)
{
	t_vec2ui32	xy;

	xy.x = from->x;
	while (xy.x < to->x)
	{
		xy.y = from->y;
		while (xy.y < to->y)
		{
			set_image_pixel(mlx, mlx->canvas, color, &xy);
			xy.y++;
		}
		xy.x++;
	}
}
