/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_koch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 23:24:21 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/10 00:16:23 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** Some reading:
**	http://world.mathigon.org/Fractals
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
	//double		x_min;
	//double		x_max;
	//double		y_min;
	//double		y_max;

	zoom = mlx->viewport.zoom_level;
	//x_min = mlx->viewport.pos.x;
	//x_min /= zoom;
	//x_max = mlx->viewport.pos.x + mlx->viewport.size.x;
	//x_max /= zoom;
	//y_min = mlx->viewport.pos.y;
	//y_min /= zoom;
	//y_max = mlx->viewport.pos.y + mlx->viewport.size.y;
	//y_max /= zoom;

	// discard the point if it is out of bounds
	//if (x <= x_min || x >= x_max || y <= y_min || y >= y_max)
	//	return;

	// x * width/2 * zoom
	// 1 * 512 * 1
	// 512 * 2
	// convert to image coord
	pos.x = floor(x * (double)mlx->canvas->width * (.5f * zoom));
	pos.y = floor(y * (double)mlx->canvas->height * (.5f * zoom));
	if (pos.x >= mlx->canvas->width || pos.y >= mlx->canvas->height)
		return;
	set_image_pixel(mlx, mlx->canvas, color, &pos);
}

// 2 * 512

//
// x_min:
// -1
//
// -2
//

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

/*
**	Some more reading:
**		http://linas.org/art-gallery/escape/escape.html
*/

static int	mandel(double complex Z, double complex C, int depth)
{
	double		modulus;
	double		escape_radius = 20.f;
	double		z_real;
	double		z_imaginary;

	while (1)
	{
		Z = Z * Z + C;
		z_real = creal(Z);
		z_imaginary = cimag(Z);
		depth++;
		modulus = sqrt(z_real * z_real + z_imaginary * z_imaginary);
		if (modulus > escape_radius || depth > limit)
			break;
	}
	return (depth);
}


static void	draw_mandel(t_mlx_st *mlx)
{
	double	i;
	double	j;
	double complex	C;

	double		zoom;
	double		x_min;
	double		x_max;
	double		y_min;
	double		y_max;
	double		step_x;
	double		step_y;
	double		range_x;
	double		range_y;

	double x;
	double y;

	zoom = mlx->viewport.zoom_level;
	// GET the position
	// 0
	x = mlx->viewport.pos.x;
	y = mlx->viewport.pos.y;
	// GET the range
	range_x = mlx->viewport.size.x / zoom;
	range_y = mlx->viewport.size.y / zoom;
	// APPLY range to min max
	x_min = x - range_x / 2;
	y_min = y - range_y / 2;
	x_max = x + range_x / 2;
	y_max = y + range_y / 2;

	// SET step
	step_x = range_x / (mlx->canvas->width + 1);
	step_y = range_y / (mlx->canvas->height + 1);

	C = CMPLX(0, 0);
	i = x_min;
	while (i < x_max)
	{
		j = y_min;
		while (j < y_max)
		{
			if (i < x_min + step_x * 2
					|| i > x_max - step_x * 2
					|| j < y_min + step_y * 2
					|| j > y_max - step_y * 2)
				; //draw_viewport_point(mlx, i - x_min, j - y_min, RED);
			else
				draw_viewport_point(mlx, i - x_min, j - y_min,
										BLACK + mandel(C, CMPLX(i, j), 0) * 10);
			j += step_y;
		}
		i += step_x;
	}
}

void	draw_koch(t_mlx_st *mlx)
{
	draw_mandel(mlx);
	mlx_put_image_to_window(mlx->sess, mlx->win, mlx->canvas->img, 0, 0);
	mlx_string_put(mlx->sess, mlx->win, 30, 30, WHITE, "Please wait, computing Koch...");
	return;
}
