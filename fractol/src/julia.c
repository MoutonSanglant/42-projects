/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 10:06:34 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/07 10:06:45 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** f[{a_, b_}] := {a*a - b*b + c1, 2*a*b + c2}]
*/

int		julia(t_vec2d z, t_vec2d c, int max_depth)
{
	t_vec2d		z_;
	int			depth;

	depth = 1;
	while (depth < max_depth && fabs(z.x) + fabs(z.y) < ESCAPE_RADIUS)
	{
		z_.x = z.x;
		z_.y = z.y;
		z.x = z_.x * z_.x - z_.y * z_.y + c.x;
		z_.x += z_.x;
		z.y = z_.x * z_.y + c.y;
		depth++;
	}
	return (depth);
}
