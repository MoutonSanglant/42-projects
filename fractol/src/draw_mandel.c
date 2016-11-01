/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mandel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 01:45:27 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/31 23:34:38 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** Some reading:
**	http://world.mathigon.org/Fractals
*/

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
**	Some more reading:
**		http://linas.org/art-gallery/escape/escape.html
*/
//static int	mandel(double complex Z, double complex C, int depth, int max_iterations)
static int	mandel(double c1, double c2, int depth, int max_iterations)
{
	/*
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
		if (modulus > escape_radius || depth > max_iterations)
			break;
	}
	return (depth);
	*/
	/*/
	//  BURNING SHEEP
	double		modulus;
	double		escape_radius = 200.f;
	double		a;
	double		b;
	double		a_;
	double		b_;

	(void)max_iterations;
	a = 0;
	b = 0;
	while (1)
	{
		a_ = a;
		b_ = b;
		a = a_ * a_ - b_ * b_ + c1; // Z
		b = 2 * a_ * b_ + c2; // C
		a = (a < 0) ? -a : a;
		b = (b < 0) ? -b : b;
		modulus = a + b;
		depth++;
		//if (modulus > escape_radius || depth > max_iterations)
		if (modulus > escape_radius || depth > 100)
			break;
	}
	return (depth);
	//*/
	double		modulus;
	double		escape_radius = 20.f;
	double		a;
	double		b;
	double		a_;
	double		b_;

	a = 0;
	b = 0;
	while (1)
	{
		a_ = a;
		b_ = b;
		a = a_ * a_ - b_ * b_ + c1; // Z
		b = 2 * a_ * b_ + c2; // C
		modulus = fabs(a) + fabs(b);
		depth++;
		if (modulus > escape_radius || depth > max_iterations)
			break;
	}
	//return ((depth < 20) ? 0 : 100);
	return (depth);
	//*/
}

/*
static void	draw_mandel_img(t_mlx_st *mlx)
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
	int			max_iterations;

	colorset = ((t_fractol_st *)mlx->datas)->color_fn;
	max_iterations = ((t_fractol_st *)mlx->datas)->max_iterations;
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
	//f[z_] := z^2+C;
			draw_viewport_point(mlx, i - x_min, j - y_min,
									mandel(C, CMPLX(i, j), 0, max_iterations), colorset);
			j += step_y;
		}
		i += step_x;
	}
}
*/

static void draw_mandel2(t_mlx_st *mlx)
{
	//double complex	Z = CMPLX(0, 0);
	double	i;
	double	j;
	int		(*colorset)(int, t_fractol_st *);
	int		max_iterations;

	colorset = ((t_fractol_st *)mlx->datas)->color_fn;
	max_iterations = ((t_fractol_st *)mlx->datas)->max_iterations;
	i = mlx->viewport.x_min;
	while (i < mlx->viewport.x_max)
	{
		j = mlx->viewport.y_min;
		while (j < mlx->viewport.y_max)
		{
			// f[{a_, b_}] := {a*a - b*b + c1, 2*a*b + c2}]
			draw_viewport_point(mlx, i - mlx->viewport.x_min, j - mlx->viewport.y_min,
									mandel(i, j, 0, max_iterations), colorset);
									//mandel(Z, CMPLX(i, j), 0, max_iterations), colorset);
			j += mlx->viewport.step_y;
			//j += 0.01;
		}
		i += mlx->viewport.step_x;
		//i += 0.01;
	}
}

void	draw_mandel(t_mlx_st *mlx)
{
	char	*str;

	ft_asprintf(&str, "Number of iterations: %i", ((t_fractol_st *)mlx->datas)->max_iterations);
	//draw_mandel_img(mlx);
	draw_mandel2(mlx);
	mlx_string_put(mlx->sess, mlx->win, 10, mlx->canvas->height - 60, WHITE, str);
	mlx_string_put(mlx->sess, mlx->win, 10, mlx->canvas->height - 30, WHITE, "Press ? for help");
	ft_strdel(&str);
	return;
}
