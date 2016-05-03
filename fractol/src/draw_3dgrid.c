/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3dgrid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 17:52:02 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/04 01:16:24 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
**	Pass vertex from world space to screen space
*/

static int		compute_point(t_mlx_st *mlx, t_vec3f *vertex,
								t_vec3f *screen_out)
{
	t_image		*canvas;

	canvas = mlx->canvas;
	*screen_out = apply_matrix4(*vertex, mlx->projection);
	if (screen_out->x < -1.f || screen_out->x > 1.f
			|| screen_out->y < -1.f || screen_out->y > 1.f)
		return (0);
	screen_out->x = fminf(canvas->width - 1.f,
			((uint32_t)((screen_out->x + 1.f) * 0.5f * canvas->width)));
	screen_out->y = fminf(canvas->height - 1.f,
			((uint32_t)((1.f - (screen_out->y + 1.f) * 0.5f) * canvas->height)));
	screen_out->z = screen_out->z;
	return (1);
}

/*
**	Transformation matrix = world * view * projection;
*/

static void		draw_triangle(t_mlx_st *mlx, t_tri *triangles, t_mat4x4 *mvp,
								void (*draw_fn)(t_mlx_st *, t_tri *))
{
	t_vec3f	vertex[3];
	t_tri	triangle;
	int		inside_boundaries[3];
	int		i;

	i = 0;
	while (i < 3)
	{
		vertex[i] = (*triangles)[i].coord;
		vertex[i] = apply_matrix4(vertex[i], mvp);
		vertex[i] = apply_matrix4(vertex[i], mlx->world_to_camera);
		inside_boundaries[i] = compute_point(mlx, &vertex[i],
												&triangle[i].coord);
		triangle[i].coord.z = 1 / triangle[i].coord.z;
		triangle[i].color = (*triangles)[i].color;
		i++;
	}
	if (inside_boundaries[0] && inside_boundaries[1] && inside_boundaries[2])
		draw_fn(mlx, &triangle);
}

/*
**	Model to World (local-to-worl)
*/

void			draw_3dgrid(t_mlx_st *mlx)
{
	void		(*draw_fn)(t_mlx_st *, t_tri *);
	t_mat4x4	mvp;
	int			i;
	int			x;
	int			y;

	draw_fn = &rasterize;
	identity_matrix4(&mvp);
	matrix4_product(&mlx->m_model, &mvp);
	matrix4_product(mlx->world, &mvp);
	i = 0;
	x = 0;
	while (x < mlx->grid->width)
	{
		y = 0;
		while (y < mlx->grid->height)
		{
			draw_triangle(mlx, &mlx->grid->triangles[i++], &mvp, draw_fn);
			draw_triangle(mlx, &mlx->grid->triangles[i++], &mvp, draw_fn);
			y++;
		}
		x++;
	}
}
