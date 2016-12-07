/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 04:37:47 by tdefresn          #+#    #+#             */
/*   Updated: 2016/12/07 02:02:38 by tdefresn         ###   ########.fr       */
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
	t_mlx_st	*mlx;
	int			mouse_capture;

	mlx = (t_mlx_st *)p;
	x = x - (int)mlx->canvas->width / 2;
	y = y - (int)mlx->canvas->height / 2;
	mouse_capture = mlx->settings.mouse_capture;
	if (button == MOUSE_CLICK_LEFT
			&& ((t_fractol_st *)mlx->datas)->fractal->interactive)
		mouse_capture = (mouse_capture) ? 0 : 1;
	else if (button == MOUSE_SCROLL_UP)
	{
		zoom_out(mlx, (double)x, (double)y);
		move_viewport(&mlx->viewport, mlx->canvas);
	}
	else if (button == MOUSE_SCROLL_DOWN)
	{
		zoom_in(mlx, (double)x, (double)y);
		move_viewport(&mlx->viewport, mlx->canvas);
	}
	mlx->settings.mouse_capture = mouse_capture;
	mlx->need_update = 1;
	return (0);
}

int			mouse_motion_event(int x, int y, void *p)
{
	t_mlx_st	*mlx;

	mlx = (t_mlx_st *)p;
	if (!mlx->settings.mouse_capture || out_of_canvas(mlx->canvas, x, y))
		return (0);
	x -= mlx->canvas->width / 2;
	y -= mlx->canvas->height / 2;
	mlx->mouse_pos.x = (double)x / mlx->canvas->width * 4;
	mlx->mouse_pos.y = (double)y / mlx->canvas->height * 4;
	mlx->need_update = 1;
	return (0);
}
