/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_canvas.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 16:54:45 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/04 01:15:13 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#ifdef BONUS

void	clear_canvas(t_mlx_st *mlx, int clear_color)
{
	t_vec2ui32	xy;
	t_image		*canvas;

	xy.x = 0;
	canvas = mlx->canvas;
	while (xy.x < canvas->width)
	{
		xy.y = 0;
		while (xy.y < canvas->height)
		{
			set_image_pixel(mlx, mlx->canvas, clear_color, &xy);
			mlx->zbuffer[xy.x + xy.y * (canvas->width)] = FLT_MAX;
			xy.y++;
		}
		xy.x++;
	}
}

#else

void	clear_canvas(t_mlx_st *mlx, int clear_color)
{
	t_vec2ui32	xy;
	t_image		*canvas;

	xy.x = 0;
	canvas = mlx->canvas;
	while (xy.x < canvas->width)
	{
		xy.y = 0;
		while (xy.y < canvas->height)
		{
			set_image_pixel(mlx, mlx->canvas, clear_color, &xy);
			xy.y++;
		}
		xy.x++;
	}
}

#endif
