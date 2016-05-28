/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 04:37:47 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/28 15:42:20 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int				mouse_click_event(int button, int x, int y, void *p)
{
	t_mlx_st	*mlx;

	(void)x;
	(void)y;
	mlx = (t_mlx_st *)p;
	if (button == MOUSE_CLICK_LEFT)
		ft_printf("left click\n");
	else if (button == MOUSE_CLICK_RIGHT)
		ft_printf("right click\n");
	else if (button == MOUSE_SCROLL_UP)
		ft_printf("scroll up\n");
	else if (button == MOUSE_SCROLL_DOWN)
		ft_printf("scroll down\n");
	mlx->need_update = 1;
	return (0);
}
int				mouse_move_event(int x, int y, void *p)
{
	t_mlx_st	*mlx;

	mlx = (t_mlx_st *)p;
	mlx->mouse_pos.x = (double)x / mlx->canvas->width;
	mlx->mouse_pos.y = (double)y / mlx->canvas->height;
	mlx->need_update = 1;
	return (0);
}
