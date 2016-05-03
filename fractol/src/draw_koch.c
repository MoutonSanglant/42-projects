/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_koch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 23:24:21 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/04 01:04:52 by tdefresn         ###   ########.fr       */
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

void	draw_koch(t_mlx_st *mlx)
{
	static t_fract	koch = { 0 };

	(void)draw_gui;

	if (!koch.ready)
	{
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
