/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 10:05:12 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/07 10:05:53 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		burning(t_vec2d z, t_vec2d c, int max_depth)
{
	t_vec2d		z_;
	int			depth;

	depth = 1;
	while (depth < max_depth && z.x + z.y < ESCAPE_RADIUS)
	{
		z_.x = z.x;
		z_.y = z.y;
		z.x = z_.x * z_.x - z_.y * z_.y + c.x;
		z_.x += z_.x;
		z.y = z_.x * z_.y + c.y;
		z.x = (z.x < 0) ? -z.x : z.x;
		z.y = (z.y < 0) ? -z.y : z.y;
		depth++;
	}
	return (depth);
}
