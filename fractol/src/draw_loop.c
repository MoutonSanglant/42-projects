/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 14:16:46 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/04 00:03:19 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#ifdef BONUS

int			draw_loop(void *p)
{
	t_mlx_st		*mlx;
	struct timeval	tval_now;
	struct timeval	tval_tic;

	mlx = (t_mlx_st *)p;
	gettimeofday(&tval_now, NULL);
	timersub(&tval_now, &mlx->last_tval, &tval_tic);
	if (tval_tic.tv_usec > FPS && mlx->need_update)
	{
		gettimeofday(&mlx->last_tval, NULL);
		clear_canvas(mlx, mlx->options.bg_color);
		mlx->draw_fn(mlx);
		//draw_3dgrid(mlx);
		mlx->need_update = 0;
	}
	return (0);
}

#else

int			draw_loop(void *p)
{
	t_mlx_st		*mlx;

	mlx = (t_mlx_st *)p;
	if (mlx->need_update)
	{
		clear_canvas(mlx, mlx->options.bg_color);
		mlx->draw_fn(mlx);
		//draw_3dgrid(mlx);
		mlx->need_update = 0;
	}
	return (0);
}

#endif
