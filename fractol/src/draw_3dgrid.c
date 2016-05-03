/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3dgrid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 17:52:02 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/03 19:15:09 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
**	Pass vertex from world space to screen space
*/

static int		compute_point(t_mlx_sess *sess, t_vec3f *vertex,
								t_vec3f *screen_out)
{
	*screen_out = apply_matrix4(*vertex, sess->projection);
	if (screen_out->x < -1.f || screen_out->x > 1.f
			|| screen_out->y < -1.f || screen_out->y > 1.f)
		return (0);
	screen_out->x = fminf(sess->width - 1.f,
			((uint32_t)((screen_out->x + 1.f) * 0.5f * sess->width)));
	screen_out->y = fminf(sess->height - 1.f,
			((uint32_t)((1.f - (screen_out->y + 1.f) * 0.5f) * sess->height)));
	screen_out->z = screen_out->z;
	return (1);
}

/*
**	Transformation matrix = world * view * projection;
*/

static void		draw_triangle(t_mlx_sess *sess, t_tri *triangles, t_mat4x4 *mvp,
								void (*draw_fn)(t_mlx_sess *, t_tri *))
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
		vertex[i] = apply_matrix4(vertex[i], sess->world_to_camera);
		inside_boundaries[i] = compute_point(sess, &vertex[i],
												&triangle[i].coord);
		triangle[i].coord.z = 1 / triangle[i].coord.z;
		triangle[i].color = (*triangles)[i].color;
		i++;
	}
	if (inside_boundaries[0] && inside_boundaries[1] && inside_boundaries[2])
		draw_fn(sess, &triangle);
}

/*
**	Model to World (local-to-worl)
*/

void			draw_3dgrid(t_mlx_sess *sess)
{
	void		(*draw_fn)(t_mlx_sess *, t_tri *);
	t_mat4x4	mvp;
	int			i;
	int			x;
	int			y;

	draw_fn = &rasterize;
	identity_matrix4(&mvp);
	matrix4_product(&sess->m_model, &mvp);
	matrix4_product(sess->world, &mvp);
	i = 0;
	x = 0;
	while (x < sess->grid->width)
	{
		y = 0;
		while (y < sess->grid->height)
		{
			draw_triangle(sess, &sess->grid->triangles[i++], &mvp, draw_fn);
			draw_triangle(sess, &sess->grid->triangles[i++], &mvp, draw_fn);
			y++;
		}
		x++;
	}
}
