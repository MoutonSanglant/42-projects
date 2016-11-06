/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport->c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 10:54:42 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/06 23:13:52 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		zoom_in(t_mlx_st *mlx, int x, int y)
{
	mlx->viewport.pos.x += x;
	mlx->viewport.pos.y += y;
	mlx->viewport.zoom_level *= 1.1;
	zoom_viewport(&mlx->viewport);
}

void		zoom_out(t_mlx_st *mlx, int x, int y)
{
	mlx->viewport.pos.x += x;
	mlx->viewport.pos.y += y;
	mlx->viewport.zoom_level *= .9;
	zoom_viewport(&mlx->viewport);
}

void		zoom_viewport(t_viewport *viewport)
{
	double		zoom;

	zoom = viewport->zoom_level;
	viewport->range.y = viewport->size.y / zoom;
	viewport->range.x = viewport->size.x / zoom;
}

void		move_viewport(t_viewport *viewport, t_image *canvas)
{
	double		x;
	double		y;
	double		range_x;
	double		range_y;

	range_y = viewport->range.y;
	range_x = viewport->range.x;
	y = viewport->pos.y;
	x = viewport->pos.x;
	viewport->min.y = y - range_y / 2;
	viewport->min.x = x - range_x / 2;
	viewport->max.y = y + range_y / 2;
	viewport->max.x = x + range_x / 2;
	viewport->step.y = range_y / (canvas->height + 1);
	viewport->step.x = range_x / (canvas->width + 1);
}
