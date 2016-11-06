/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mandel_complex.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 12:59:31 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/06 17:32:25 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	draw_viewport_point(t_mlx_st *mlx, double x, double y, int color,
							int (color_fn)(int, t_fractol_st *))
{
	t_vec2ui32	pos;
	double		zoom;

	zoom = mlx->viewport.zoom_level;
	color = color_fn(color, ((t_fractol_st *)mlx->datas));
	pos.x = floor(x * (double)mlx->canvas->width * (.5f * zoom));
	pos.y = floor(y * (double)mlx->canvas->height * (.5f * zoom));
	if (pos.x >= mlx->canvas->width || pos.y >= mlx->canvas->height)
		return;
	set_image_pixel(mlx, mlx->canvas, color, &pos);
}

/*
** f[z_] := z^2+C;
*/
static int	mandel(double complex Z, double complex C, int depth, int max_depth)
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
		if (modulus > escape_radius || depth > max_depth)
			break;
	}
	return (depth);
}

static void	ddraw(t_mlx_st *mlx)
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

	int			(*colorset)(int, t_fractol_st *);
	int			iterations;

	colorset = ((t_fractol_st *)mlx->datas)->color_fn;
	iterations = ((t_fractol_st *)mlx->datas)->iterations;
	zoom = mlx->viewport.zoom_level;
	x = mlx->viewport.pos.x;
	y = mlx->viewport.pos.y;
	range_x = mlx->viewport.size.x / zoom;
	range_y = mlx->viewport.size.y / zoom;
	x_min = x - range_x / 2;
	y_min = y - range_y / 2;
	x_max = x + range_x / 2;
	y_max = y + range_y / 2;
	step_x = range_x / (mlx->canvas->width + 1);
	step_y = range_y / (mlx->canvas->height + 1);
	C = CMPLX(0, 0);
	i = x_min;
	while (i < x_max)
	{
		j = y_min;
		while (j < y_max)
		{
			draw_viewport_point(mlx, i - x_min, j - y_min,
									mandel(C, CMPLX(i, j), 0, iterations), colorset);
			j += step_y;
		}
		i += step_x;
	}
}

void	draw_mandel_complex(t_mlx_st *mlx)
{
	char	str[28];

	ddraw(mlx);
	mlx_put_image_to_window(mlx->sess, mlx->win, mlx->canvas->img, 0, 0);
	ft_sprintf(str, "Number of iterations: %i", ((t_fractol_st *)mlx->datas)->iterations);
	mlx_string_put(mlx->sess, mlx->win, 10, mlx->canvas->height - 60, WHITE, str);
	mlx_string_put(mlx->sess, mlx->win, 10, mlx->canvas->height - 30, WHITE, "Press ? for help");
}
