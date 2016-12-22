/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 09:01:01 by tdefresn          #+#    #+#             */
/*   Updated: 2016/12/07 09:16:53 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <complex.h>

#include "fractol.h"

/*
**	z1 = z1 * z1 + c1;
*/

int		shell(t_vec2d *z, t_vec2d *c, int depth, int max_depth)
{
	double _Complex	z1;
	double _Complex	c1;

	c1 = z->x + z->y * _Complex_I;
	z1 = c->x + c->y * _Complex_I;
	depth = max_depth;
	while (depth--)
	{
		z1 = cpow(z1, 1.5) + 0.2;
		if (cabs(z1) > ESCAPE_RADIUS)
			break ;
	}
	return (max_depth - depth);
}
