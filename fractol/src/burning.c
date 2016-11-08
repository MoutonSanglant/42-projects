/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 10:05:12 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/08 03:18:58 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		burning(t_vec2d *z, t_vec2d *c, int depth, int max_depth)
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
	//while (depth < max_depth && z->x + z->y < ESCAPE_RADIUS)
	while (depth-- && xx + yy < ESCAPE_RADIUS)
	{
		xy = x * y;
		xx = x * x;
		yy = y * y;
		x = xx - yy + c->x;
		y = xy + xy + c->y;
		x = (x < 0) ? -x : x;
		y = (y < 0) ? -y : y;
	}
	return (max_depth - depth);
}
