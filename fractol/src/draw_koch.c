/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_koch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 23:24:21 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/05 20:03:09 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int g_degree = 0;
int g_degree_limit = 10;

/*
** First, some reading:
**	http://world.mathigon.org/Fractals
** What we need:
**	complex numbers:
**	x (real part)
**	is added to
**	y * i (where i equals sqrt(-1)) (imaginary part)
**
**	A viewport
*/

void	pixel(t_mlx_st *mlx, uint32_t x, uint32_t y)
{
	t_vec2ui32	pos;

	pos.x = x;
	pos.y = y;
	set_image_pixel(mlx, mlx->canvas, RED, &pos);
}

void	draw_viewport_point(t_mlx_st *mlx, double x, double y, int color)
{
	t_vec2ui32	pos;
	double		zoom;
	double		x_min;
	double		x_max;
	double		y_min;
	double		y_max;

	zoom = mlx->viewport.zoom_level;

	// range
	x_min = -1 / zoom;
	x_max = 1 / zoom;
	y_min = -1 / zoom;
	y_max = 1 / zoom;

	// discard the point if it is out of bounds
	// TODO
	// 1.f should vary with zoom level
	if (fabs(x) >= x_max || fabs(y) >= y_max)
		return;
	// convert to image coord

	pos.x = floor((x + x_max) * (double)mlx->canvas->width * (.5f * zoom));
	pos.y = floor((y + y_max) * (double)mlx->canvas->height * (.5f * zoom));
	//if (zoom > 1)
	//	printf("x: %f -> %i, y: %f -> %i\n", x, pos.x, y, pos.y);
	set_image_pixel(mlx, mlx->canvas, color, &pos);
}

// range [-0.5, 0.5]
// -0.5
// -0.5 + 0.5 = 0
// 0 * 512 * 2 = 0

// 0.5
// 0.5 + 0.5 = 1
// 1 * 512 * 2 = 1024

// 2
// 2 + 2 = 4
// 4 * 512 * 0.5 = 

// range:
// [-2, 2]
// -2
// -2 + 2 = 0
// 0 * 512 = 0

// viewport range:
// example for x (res: 1024)
// 1024/2 = 512;
// (x/512) - 1
//
// to px:
// 0.5
// 0.5 + 1 = 1.5
// 1.5 * 512 = 768

int limit = 20;
#define EPSILON 0.000000001f

static int	mandel(double complex Z, double complex C, int depth)
{
	complex double	Z1;

	Z1 = Z * Z + C;
	if (cabs(Z1) > 2)
		return (WHITE);
	else if (depth < limit)
		return (mandel(Z1, C, ++depth));
	//else
	//	return (WHITE);
	return (BLACK);
	//if (fabs(z1) - fabs(z) < EPSILON)
	//	return (BLACK);
	//else
}


static void	draw_mandel(t_mlx_st *mlx)
{
	double	i;
	double	j;
	int		col;
	double complex	Z;
	double complex	C;

	double		zoom;
	double		x_min;
	double		x_max;
	double		y_min;
	double		y_max;
	double		step;

	zoom = mlx->viewport.zoom_level;
	x_min = -1.f / zoom;
	x_max = 1.f / zoom;
	y_min = -1.f / zoom;
	y_max = 1.f / zoom;
	step = .001f;
	C = CMPLX(0, 0);

	i = x_min;
	while (i < x_max)
	{
		j = y_min;
		while (j < y_max)
		{
			//col = mandel(0, i * j * im, 0);
			Z = CMPLX(i, j);
			col = mandel(C, Z, 0);
			draw_viewport_point(mlx, i, j, col);
			j += step;
		}
		i += step;
	}
}

void	draw_koch(t_mlx_st *mlx)
{
	static t_fract	koch = { 0 };

	if (!koch.ready)
	{
		//draw_viewport_point(0, 0.1, 0);
		//koch.ready = 1;
		//printf("csqrt(i): %f", csqrt(-1.0));

		draw_mandel(mlx);

		mlx_put_image_to_window(mlx->sess, mlx->win, mlx->canvas->img, 0, 0);
		mlx_string_put(mlx->sess, mlx->win, 30, 30, WHITE, "Please wait, computing Koch...");
		//draw_gui(sess);
		return;
	}
	else
	{
	}
	t_vec2f from;
	t_vec2f to;

	double precision;
	int color = RED;

	g_degree++;
	if (g_degree == 2)
		color = BLUE;
	if (g_degree == 3)
		color = GREEN;
	if (g_degree == 4)
		color = RED + BLUE;
	if (g_degree == 5)
		color = RED + GREEN;
	if (g_degree == 6)
		color = GREEN + BLUE;

	precision = 1 / (double)g_degree;
	from.x = 10 * precision;
	from.y = 10 * precision;
	to.x = 300 * precision;
	to.y = 300 * precision;
	draw_square(mlx, color, &from, &to);
	//return;
	if (g_degree < g_degree_limit)
		draw_koch(mlx);
	g_degree = 0;
}
