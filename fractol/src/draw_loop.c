/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 14:16:46 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/07 23:06:36 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#ifdef BONUS

static int	get_fps(t_mlx_st *mlx)
{
	static int		frames = 0;
	static double	fps = 0;
	struct timeval	tval_now;

	frames++;
	gettimeofday(&tval_now, NULL);
	timersub(&tval_now, &mlx->last_tval, &tval_now);
	if (tval_now.tv_sec * 1000000 + tval_now.tv_usec > 1000000)
	{
		fps = (double)frames / (double)tval_now.tv_sec
			+ (double)tval_now.tv_usec / 1000000;
		fps = (fps > 60) ? 60 : fps;
		gettimeofday(&mlx->last_tval, NULL);
		mlx->need_update = 1;
		frames = 0;
	}
	return ((int)fps);
}

int			draw_loop(void *p)
{
	t_mlx_st	*mlx;
	char		str[7];
	int			fps;

	mlx = (t_mlx_st *)p;
	fps = get_fps(mlx);
	if (mlx->need_update)
	{
		mlx->draw_fn(mlx);
		ft_snprintf(str, 7, "%2.2i FPS", fps);
		mlx_string_put(mlx->sess, mlx->win,
				mlx->canvas->width - 80, 4, WHITE, str);
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
		mlx->draw_fn(mlx);
		mlx->need_update = 0;
	}
	return (0);
}

#endif
