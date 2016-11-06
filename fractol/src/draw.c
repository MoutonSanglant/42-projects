/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 16:59:49 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/06 23:11:19 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	draw_ui(t_mlx_st *mlx, int iterations)
{
	void	*win;
	void	*sess;
	t_image	*canvas;
	char	str[32];

	win = mlx->win;
	sess = mlx->sess;
	canvas = mlx->canvas;
	mlx_put_image_to_window(sess, win, canvas->img, 0, 0);
	ft_sprintf(str, "Number of iterations: %i", iterations);
	mlx_string_put(sess, win, 10, canvas->height - 60, WHITE, str);
	mlx_string_put(sess, win, 10, canvas->height - 30, WHITE, "Press ? for help");
	mlx_string_put(sess, win, canvas->width * 0.5f - 20, 10, WHITE, ((t_fractol_st *)mlx->datas)->fractal->name);
}

static void	draw_point(t_mlx_st *mlx, unsigned int x, unsigned int y, int color,
							int (color_fn)(int, t_fractol_st *))
{
	t_vec2ui32	pos;

	if (x >= mlx->canvas->width || y >= mlx->canvas->height)
		return ;
	pos.x = x;
	pos.y = y;
	color = color_fn(color, ((t_fractol_st *)mlx->datas));
	set_image_pixel(mlx, mlx->canvas, color, &pos);
}

static void	draw_viewport(t_mlx_st *mlx, t_vec2d min, t_vec2d max, t_vec2d	step)
{
	int		(*fn)(double, double, int);
	int		(*color_fn)(int, t_fractol_st *);
	int		max_depth;
	t_vec2	coord;
	t_vec2d	C;

	fn = ((t_fractol_st *)mlx->datas)->fractal->fn;
	color_fn = ((t_fractol_st *)mlx->datas)->color_fn;
	max_depth = ((t_fractol_st *)mlx->datas)->iterations;
	C.x = min.x;
	coord.x = 0;
	while (C.x < max.x)
	{
		coord.y = 0;
		C.y = min.y;
		while (C.y < max.y)
		{
			draw_point(mlx, coord.x, coord.y,
					fn(C.x * mlx->canvas->aspect, C.y, max_depth), color_fn);
			C.y += step.y;
			coord.y++;
		}
		C.x += step.x;
		coord.x++;
	}
}

void	draw(t_mlx_st *mlx)
{
	draw_viewport(mlx, mlx->viewport.min, mlx->viewport.max, mlx->viewport.step);
	draw_ui(mlx, ((t_fractol_st *)mlx->datas)->iterations);
}
