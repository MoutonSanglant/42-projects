/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 04:37:47 by tdefresn          #+#    #+#             */
/*   Updated: 2017/05/14 18:44:18 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	out_of_canvas(t_image *c, int x, int y)
{
	return (x < 0 || y < 0 || x > (int)c->width || y > (int)c->height);
}

/*
**	else if (button == MOUSE_CLICK_RIGHT)
**		ft_printf("right click\n");
*/

int			mouse_click_event(int button, int x, int y, void *p)
{
	t_context	*ctx;
	int			mouse_capture;

	ctx = (t_context *)p;
	x = x - (int)ctx->canvas->width / 2;
	y = y - (int)ctx->canvas->height / 2;
	mouse_capture = ctx->settings.mouse_capture;
	if (button == MOUSE_CLICK_LEFT
			&& ((t_fractol_st *)ctx->datas)->fractal->interactive)
		mouse_capture = (mouse_capture) ? 0 : 1;
	else if (button == MOUSE_SCROLL_UP)
	{
		zoom_out(ctx, (double)x, (double)y);
		move_viewport(&ctx->viewport, ctx->canvas);
	}
	else if (button == MOUSE_SCROLL_DOWN)
	{
		zoom_in(ctx, (double)x, (double)y);
		move_viewport(&ctx->viewport, ctx->canvas);
	}
	ctx->settings.mouse_capture = mouse_capture;
	ctx->need_update = 1;
	return (0);
}

int			mouse_motion_event(int x, int y, void *p)
{
	t_context	*ctx;

	ctx = (t_context *)p;
	if (!ctx->settings.mouse_capture || out_of_canvas(ctx->canvas, x, y))
		return (0);
	x -= ctx->canvas->width / 2;
	y -= ctx->canvas->height / 2;
	ctx->mouse_pos.x = (double)x / ctx->canvas->width * 4;
	ctx->mouse_pos.y = (double)y / ctx->canvas->height * 4;
	ctx->need_update = 1;
	return (0);
}
