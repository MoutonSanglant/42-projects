/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 17:59:54 by tdefresn          #+#    #+#             */
/*   Updated: 2017/05/14 18:29:01 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
**	Step 1:
**	mouse to viewport
**	Step 2:
**	center viewport to mouse position
**	Step 3:
**	zoom viewport
**	Step 4:
**	move back from offset (mouse pos after zoom)
*/

void		zoom_in(t_context *ctx, double x, double y)
{
	t_viewport	*viewport;

	viewport = &ctx->viewport;
	x = (x / ctx->canvas->width) * 2;
	y = (y / ctx->canvas->height) * 2;
	viewport->pos.x += x / viewport->zoom_level;
	viewport->pos.y += y / viewport->zoom_level;
	viewport->zoom_level *= 1.1;
	zoom_viewport(&ctx->viewport);
	viewport->pos.x -= x / viewport->zoom_level;
	viewport->pos.y -= y / viewport->zoom_level;
}

void		zoom_out(t_context *ctx, double x, double y)
{
	t_viewport	*viewport;

	viewport = &ctx->viewport;
	x = (x / ctx->canvas->width) * 2;
	y = (y / ctx->canvas->height) * 2;
	viewport->pos.x += x / viewport->zoom_level;
	viewport->pos.y += y / viewport->zoom_level;
	viewport->zoom_level *= .9;
	zoom_viewport(&ctx->viewport);
	viewport->pos.x -= x / viewport->zoom_level;
	viewport->pos.y -= y / viewport->zoom_level;
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
