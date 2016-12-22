/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel_spider.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 09:28:11 by tdefresn          #+#    #+#             */
/*   Updated: 2016/12/07 09:28:11 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		mandel_spider(t_vec2d *z, t_vec2d *c, int depth, int max_depth)
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
	while (depth-- && xx * yy < ESCAPE_RADIUS)
	{
		xy = x * y;
		xx = x * x;
		yy = y * y;
		x = xx - yy + c->x;
		y = xy + xy + c->y;
	}
	return (max_depth - depth);
}
