/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 12:57:31 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/09 12:57:38 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** f[{a_, b_}] := {a*a - b*b + c1, 2*a*b + c2}]
*/

int		mandelbrot(t_vec2d *z, t_vec2d *c, int depth, int max_depth)
{
	double		xy;
	double		xx;
	double		yy;
	double		x;
	double		y;

	xx = 0;
	xy = 0;
	yy = 0;
	x = z->x;
	y = z->y;
	depth = max_depth;
	while (depth-- && xx + yy < ESCAPE_RADIUS)
	{
		xy = x * y;
		xx = x * x;
		yy = y * y;
		x = xx - yy + c->x;
		y = xy + xy + c->y;
	}
	return (max_depth - depth);
}
