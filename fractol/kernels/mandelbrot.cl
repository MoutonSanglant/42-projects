/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.cl                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 11:44:28 by tdefresn          #+#    #+#             */
/*   Updated: 2017/05/21 11:44:28 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Simple OpenCL kernel that squares an input array.
*/

#pragma OPENCL EXTENSION cl_khr_fp64 : enable

#define ESCAPE_RADIUS 4.0

kernel void mandelbrot(int width, double zoom_level, int max_depth, global double *out)
{
	double		xy;
	double		xx;
	double		yy;
	double		x;
	double		y;
	double		cx;
	double		cy;
	size_t		i;
	size_t		j;
	int			depth;

	i = get_global_id(0);
	j = get_global_id(1);

	x = get_global_id(0) * zoom_level;
	y = get_global_id(1) * zoom_level;
	/*y = (x / width) * zoom_level;*/
	/*x = (fmod(x, width)) * zoom_level;*/

	xx = 0;
	xy = 0;
	yy = 0;
	depth = max_depth;
	while (depth-- && xx + yy < ESCAPE_RADIUS)
	{
		xy = x * y;
		xx = x * x;
		yy = y * y;
		x = xx - yy + cx;
		y = xy + xy + cy;
	}
	/*out[i] = max_depth - depth;*/
	out[i] = i * j;
}
