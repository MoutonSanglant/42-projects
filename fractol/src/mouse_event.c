/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 04:37:47 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/30 18:42:45 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int				mouse_click_event(int button, int x, int y, void *p)
{
	t_mlx_st	*mlx;
	int			mouse_capture;

	mlx = (t_mlx_st *)p;
	ft_printf("[mouse] x:, %i, y: %i\n", x, y);
	ft_printf("[size ] x:, %i, y: %i\n", mlx->canvas->width, mlx->canvas->height);
	x = x - (int)mlx->canvas->width / 2;
	y = y - (int)mlx->canvas->height / 2;
	mouse_capture = ((t_fractol_st *)mlx->datas)->capture_mouse_position;
	if (button == MOUSE_CLICK_LEFT && ft_strequ(((t_fractol_st *)mlx->datas)->name, "Julia"))
		mouse_capture = (mouse_capture) ? 0 : 1;
	else if (button == MOUSE_CLICK_RIGHT)
		ft_printf("right click\n");
	else if (button == MOUSE_SCROLL_UP)
		zoom_in(mlx, x, y);
	else if (button == MOUSE_SCROLL_DOWN)
		zoom_out(mlx, x, y);
	mlx->need_update = 1;
	((t_fractol_st *)mlx->datas)->capture_mouse_position = mouse_capture;
	return (0);
}
int				mouse_motion_event(int x, int y, void *p)
{
	t_mlx_st	*mlx;

	mlx = (t_mlx_st *)p;
	if (!((t_fractol_st *)mlx->datas)->capture_mouse_position
			|| x < 0 || y < 0 || x > (int)mlx->canvas->width || y > (int)mlx->canvas->height)
		return (0);
	x -= mlx->canvas->width / 2;
	y -= mlx->canvas->height / 2;
	mlx->mouse_pos.x = (double)x / mlx->canvas->width * 4;
	mlx->mouse_pos.y = (double)y / mlx->canvas->height * 4;
	mlx->need_update = 1;
	return (0);
}
