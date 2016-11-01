/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 10:54:42 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/30 10:59:17 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		set_viewport(t_mlx_st *mlx)
{
	double		x;
	double		y;
	double		zoom;
	double		range_x;
	double		range_y;

	zoom = mlx->viewport.zoom_level;
	x = mlx->viewport.pos.x;
	y = mlx->viewport.pos.y;
	range_x = mlx->viewport.size.x / zoom;
	range_y = mlx->viewport.size.y / zoom;
	mlx->viewport.x_min = x - range_x / 2;
	mlx->viewport.y_min = y - range_y / 2;
	mlx->viewport.x_max = x + range_x / 2;
	mlx->viewport.y_max = y + range_y / 2;
	mlx->viewport.step_x = range_x / (mlx->canvas->width + 1);
	mlx->viewport.step_y = range_y / (mlx->canvas->height + 1);
}
