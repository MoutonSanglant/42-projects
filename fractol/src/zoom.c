/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 18:20:35 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/30 10:58:21 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	center_to_point(t_mlx_st *mlx, int x, int y)
{
	mlx->viewport.pos.x += x;
	mlx->viewport.pos.y += y;
	//mlx->viewport.pos.x += x / mlx->viewport.zoom_level;
	//mlx->viewport.pos.y += y / mlx->viewport.zoom_level;
}

void		zoom_in(t_mlx_st *mlx, int x, int y)
{
	//ft_printf("[zoom]  x:, %i, y: %i\n", x, y);
	//mlx->viewport.zoom_level *= 2.f;
	center_to_point(mlx, x, y);
	mlx->viewport.zoom_level *= 1.1f;
}

void		zoom_out(t_mlx_st *mlx, int x, int y)
{
	//mlx->viewport.zoom_level *= .5f;
	center_to_point(mlx, x, y);
	mlx->viewport.zoom_level *= .9f;
}
