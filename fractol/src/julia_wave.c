/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_wave.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 09:11:08 by tdefresn          #+#    #+#             */
/*   Updated: 2016/12/07 09:16:18 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <complex.h>

#include "fractol.h"

/*
**	z1 = z1 * z1 + c1;
*/

int		julia_wave(t_vec2d *z, t_vec2d *c, int depth, int max_depth)
{
	double _Complex	z1;

	(void)z;
	z1 = c->x + c->y * _Complex_I;
	depth = max_depth;
	while (depth--)
	{
		z1 = cpow(z1, -2) + 0.653125 + 0.510337 * _Complex_I;
		if (cabs(z1) > ESCAPE_RADIUS)
			break ;
	}
	return (max_depth - depth);
}
