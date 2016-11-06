/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport->c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 10:54:42 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/06 19:26:49 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		set_viewport(t_viewport *viewport, t_image *canvas)
{
	double		x;
	double		y;
	double		zoom;
	double		range_x;
	double		range_y;

	zoom = viewport->zoom_level;
	y = viewport->pos.y;
	x = viewport->pos.x;
	range_y = viewport->size.y / zoom;
	range_x = viewport->size.x / zoom;
	viewport->min.y = y - range_y / 2;
	viewport->min.x = x - range_x / 2;
	viewport->max.y = y + range_y / 2;
	viewport->max.x = x + range_x / 2;
	viewport->step.y = range_y / (canvas->height + 1);

	// TODO Not good
	viewport->step.x = viewport->step.y / canvas->aspect;
}
