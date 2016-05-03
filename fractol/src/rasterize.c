/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 12:41:37 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/04 01:17:17 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	set_pix_z(t_mlx_st *mlx, t_vec2ui32 *xy, float z)
{
	unsigned char	r;
	int				col;

	r = 0;
	col = mlx->options.lines_color;
	if ((*mlx->projection)[15] < 0.00001f)
		r = (unsigned char)(fminf(fmaxf(z * 254.f, 0.f), 254.f)
				* mlx->options.distance - 254.f * mlx->options.distance);
	else
		r = (unsigned char)(fminf(fmaxf((z - 49.f) * 254.f, 0.f), 254.f));
	col = ((int)r << 16) | ((int)r << 8) | (r);
	set_image_pixel(mlx, mlx->canvas, mlx_get_color_value(mlx->sess, col), xy);
}

static void	set_pix(t_mlx_st *mlx, t_vec2ui32 *xy,
								float w[3], t_tri triangle)
{
	float	r;
	float	g;
	float	b;
	int		col;

	col = mlx->options.faces_color;
	if (mlx->options.fill_faces || !(w[0] >= mlx->options.line_width
			&& w[1] >= mlx->options.line_width && w[2] >= 0))
	{
		r = w[0] * triangle[0].color.r + w[1] * triangle[1].color.r
				+ w[2] * triangle[2].color.r;
		g = w[0] * triangle[0].color.g + w[1] * triangle[1].color.g
				+ w[2] * triangle[2].color.g;
		b = w[0] * triangle[0].color.b + w[1] * triangle[1].color.b
				+ w[2] * triangle[2].color.b;
		col = ((int)(r * 255) << 16) | ((int)(g * 255) << 8) | ((int)(b * 255));
	}
	set_image_pixel(mlx, mlx->canvas, mlx_get_color_value(mlx->sess, col), xy);
}

/*
**	Compute the edge function of the pixel and get it's weight
*/

static void	compute_fragment(t_mlx_st *mlx,
							t_tri t, t_vec2ui32 *xy, float area)
{
	t_image		*canvas;
	t_vec3f		pixel_sample;
	float		one_over_z;
	float		w[3];
	float		z;

	canvas = mlx->canvas;
	pixel_sample.x = xy->x;
	pixel_sample.y = xy->y;
	pixel_sample.z = 0;
	w[0] = EDGE_FN(t[1].coord, t[2].coord, pixel_sample);
	w[1] = EDGE_FN(t[2].coord, t[0].coord, pixel_sample);
	w[2] = EDGE_FN(t[0].coord, t[1].coord, pixel_sample);
	if (w[0] >= 0.f && w[1] >= 0.f && w[2] >= 0.f)
	{
		w[0] /= area;
		w[1] /= area;
		w[2] /= area;
		one_over_z = (t)[0].coord.z * w[0]
				+ (t)[1].coord.z * w[1] + (t)[2].coord.z * w[2];
		z = one_over_z;
		if (z < mlx->zbuffer[xy->x + xy->y * canvas->width])
		{
			mlx->zbuffer[xy->x + xy->y * canvas->width] = z;
			(mlx->options.zdraw) ? set_pix_z(mlx, xy, z)
									: set_pix(mlx, xy, w, t);
		}
	}
}

static int	compute_bb(t_mlx_st *mlx,
						t_tri triangle, t_vec2ui32 *min, t_vec2ui32 *max)
{
	t_image		*canvas;
	float	xmin;
	float	xmax;
	float	ymin;
	float	ymax;

	canvas = mlx->canvas;
	xmin = MIN3(triangle[0].coord.x, triangle[1].coord.x, triangle[2].coord.x);
	xmax = MAX3(triangle[0].coord.x, triangle[1].coord.x, triangle[2].coord.x);
	ymin = MIN3(triangle[0].coord.y, triangle[1].coord.y, triangle[2].coord.y);
	ymax = MAX3(triangle[0].coord.y, triangle[1].coord.y, triangle[2].coord.y);
	if (xmin > canvas->width - 1 || xmax < 0 || ymin > canvas->height - 1 || ymax < 0)
		return (0);
	min->x = (uint32_t)fmaxf(0.f, floorf(xmin));
	max->x = (uint32_t)fminf(canvas->width - 1, floorf(xmax));
	min->y = (uint32_t)fmaxf(0.f, floorf(ymin));
	max->y = (uint32_t)fminf(canvas->height - 1, floorf(ymax));
	return (1);
}

/*
**	Actually, there is no top-left rule check
**	It should be done just after the bb test
*/

void		rasterize(t_mlx_st *mlx, t_tri *triangle)
{
	float		area;
	t_vec2ui32	min;
	t_vec2ui32	max;
	t_vec2ui32	xy;

	if (!compute_bb(mlx, *triangle, &min, &max))
		return ;
	area = EDGE_FN((*triangle)[0].coord,
					(*triangle)[1].coord, (*triangle)[2].coord);
	xy.y = min.y;
	while (xy.y < max.y)
	{
		xy.y++;
		xy.x = min.x;
		while (xy.x < max.x)
		{
			compute_fragment(mlx, *triangle, &xy, area);
			xy.x++;
		}
	}
}
