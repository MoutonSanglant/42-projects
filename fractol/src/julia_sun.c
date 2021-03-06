/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_sun.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 09:11:13 by tdefresn          #+#    #+#             */
/*   Updated: 2016/12/07 09:16:42 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <complex.h>

#include "fractol.h"

/*
**	z1 = z1 * z1 + c1;
*/

int		julia_sun(t_vec2d *z, t_vec2d *c, int depth, int max_depth)
{
	double _Complex	z1;

	(void)z;
	z1 = c->x + c->y * _Complex_I;
	depth = max_depth;
	while (depth--)
	{
		z1 = cpow(z1, -10) + 0.007 + 1.023 * _Complex_I;
		if (cabs(z1) > ESCAPE_RADIUS)
			break ;
	}
	return (max_depth - depth);
}
