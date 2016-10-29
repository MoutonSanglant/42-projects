/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 14:16:46 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/29 07:22:29 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#ifdef BONUS

int			draw_loop(void *p)
{
	static int		frames = 0;
	static double	fps = 0;
	char			str[7];
	t_mlx_st		*mlx;
	struct timeval	tval_now;

	mlx = (t_mlx_st *)p;
	gettimeofday(&tval_now, NULL);
	timersub(&tval_now, &mlx->last_tval, &tval_now);
	frames++;
	if (tval_now.tv_sec * 1000000 + tval_now.tv_usec > 1000000)
	{
		fps = (double)frames / (double)tval_now.tv_sec + (double)tval_now.tv_usec / 1000000;
		frames = 0;
		gettimeofday(&mlx->last_tval, NULL);
	}
	clear_canvas(mlx, mlx->options.bg_color);
	mlx->draw_fn(mlx);
	mlx_put_image_to_window(mlx->sess, mlx->win, mlx->canvas->img, 0, 0);
	//draw_3dgrid(mlx);
	//TODO use ft_snprinf
	snprintf(str, 7, "%2.2i FPS", (int)fps);
	mlx_string_put(mlx->sess, mlx->win, mlx->canvas->width - 100, 20, WHITE, str);
	mlx->need_update = 0;
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
