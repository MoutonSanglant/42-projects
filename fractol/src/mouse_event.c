/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 04:37:47 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/28 05:25:38 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//int				mouse_event(int button, int x, int y, void *p)
int				mouse_event(int x, int y, void *p)
{
	t_mlx_st	*mlx;

	//(void) button;
	mlx = (t_mlx_st *)p;
	mlx->mouse_pos.x = (double)x / mlx->canvas->width;
	mlx->mouse_pos.y = (double)y / mlx->canvas->height;
	mlx->need_update = 1;
	return (0);
	//ft_printf("x: %i\ny: %i\n=====\n", x, y);
	//ft_printf("x: %i\ny: %i\n=====\n", x, y);
}
