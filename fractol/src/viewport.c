/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 17:59:54 by tdefresn          #+#    #+#             */
/*   Updated: 2016/12/07 00:18:50 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		zoom_in(t_mlx_st *mlx, double x, double y)
{
	t_viewport	*viewport;
	t_image		*canvas;
	double		zoom_factor;
	double		offset_x;
	double		offset_y;

	viewport = &mlx->viewport;
	viewport->zoom_level *= 1.1;
	zoom_viewport(&mlx->viewport);
	printf("viewport range x: %f, y: %f\n", viewport->range.x, viewport->range.y);
	printf("viewport pos x: %f, y: %f\n", viewport->pos.x, viewport->pos.y);
	printf("viewport min x: %f, y: %f\n", viewport->min.x, viewport->min.y);
	x = viewport->pos.x - viewport->range.x / 2;
	y = viewport->pos.y - viewport->range.y / 2;
	printf("viewport left x: %f, y: %f\n", x, y);
	viewport->min.x = x;
	viewport->min.y = y;
	return ;
	printf("mouse x: %f, y: %f\n", x, y);
	canvas = mlx->canvas;
	zoom_factor = viewport->zoom_level;
	zoom_factor = viewport->zoom_level - zoom_factor;
	x = (x - viewport->pos.x) * viewport->zoom_level + viewport->pos.x;
	y = (y - viewport->pos.y) * viewport->zoom_level + viewport->pos.y;
	x = x / mlx->canvas->width;
	y = y / mlx->canvas->height;
	printf("new x: %f, y: %f\n", x, y);
	offset_x = (x * zoom_factor);
	offset_y = (y * zoom_factor);
	//printf("offset x: %f, y: %f\n", offset_x, offset_y);
	printf("viewport pos x: %f, y: %f\n", viewport->pos.x, viewport->pos.y);
	//printf("viewport range x: %f, y: %f\n", viewport->range.x, viewport->range.y);
	//viewport->pos.x += x *;
	//viewport->pos.y += y;
	offset_x = x;
	offset_y = y;
	viewport->pos.x = x;
	viewport->pos.y = y;
	//viewport->pos.x += x * zoom_factor;
	//viewport->pos.y += y * zoom_factor;
	//viewport->pos.x = x - viewport->size.x * zoom_factor;
	//viewport->pos.y = y - viewport->size.y * zoom_factor;
	//viewport->pos.x = x + viewport->pos.x * zoom_factor;
	//viewport->pos.y = y + viewport->pos.y * zoom_factor;

	//x = x - canvas->width * zoom_factor;
	//y = y - canvas->height * zoom_factor;
	//viewport->pos.x = x * (1.1 - 1) + 1.1 * canvas->width;
	//viewport->pos.y = y * (1.1 - 1) + 1.1 * canvas->height;
	printf(">>> viewport pos x: %f, y: %f\n", viewport->pos.x, viewport->pos.y);
}

void		zoom_out(t_mlx_st *mlx, double x, double y)
{
	/*
	double	last_x;
	double	last_y;

	last_x = mlx->viewport.pos.x;
	last_y = mlx->viewport.pos.y;
	mlx->viewport.pos.x = x;
	mlx->viewport.pos.y = y;
	*/
	mlx->viewport.zoom_level *= .9;
	zoom_viewport(&mlx->viewport);
	mlx->viewport.pos.x -= x;
	mlx->viewport.pos.y -= y;
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
	double		range_x;
	double		range_y;
	double		x;
	double		y;

	range_y = viewport->range.y / 2;
	range_x = viewport->range.x / 2;
	y = viewport->pos.y;
	x = viewport->pos.x;
	viewport->min.y = y - range_y;
	viewport->min.x = x - range_x;
	viewport->max.y = y + range_y;
	viewport->max.x = x + range_x;
	viewport->step.y = range_y / (canvas->height + 1) * 2;
	viewport->step.x = range_x / (canvas->width + 1) * 2;
}
