/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_grid_from_vertmap.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 13:51:35 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/06 07:50:15 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
**	1
**	|\
**	| \
**	2--0
**	Draw midline first in order to discard
**	it at rendering to produce quads
*/

static void		top_right_triangle_vertices(t_grid *grid, size_t idx,
										t_vert **vertmap, t_vec2 coord)
{
	grid->triangles[idx][0].coord.x = (float)(1.f * coord.x + 1.f);
	grid->triangles[idx][0].coord.y = (float)(1.f * coord.y + 1.f);
	grid->triangles[idx][0].coord.z =
		(float)vertmap[coord.y + 1][coord.x + 1].coord.z * 0.15f;
	grid->triangles[idx][1].coord.x = (float)(1.f * coord.x);
	grid->triangles[idx][1].coord.y = (float)(1.f * coord.y);
	grid->triangles[idx][1].coord.z =
		(float)vertmap[coord.y][coord.x].coord.z * 0.15f;
	grid->triangles[idx][2].coord.x = (float)(1.f * coord.x);
	grid->triangles[idx][2].coord.y = (float)(1.f * coord.y + 1.f);
	grid->triangles[idx][2].coord.z =
		(float)vertmap[coord.y + 1][coord.x].coord.z * 0.15f;
}

/*
**	0--2
**	 \ |
**	  \|
**	   1
**	Draw midline first in order to discard
**	it at rendering to produce quads
*/

static void		bottom_left_triangle_vertices(t_grid *grid, size_t idx,
											t_vert **vertmap, t_vec2 coord)
{
	grid->triangles[idx][1].coord.x = (float)(1.f * coord.x + 1.f);
	grid->triangles[idx][1].coord.y = (float)(1.f * coord.y + 1.f);
	grid->triangles[idx][1].coord.z =
		(float)vertmap[coord.y + 1][coord.x + 1].coord.z * 0.15f;
	grid->triangles[idx][2].coord.x = (float)(1.f * coord.x + 1.f);
	grid->triangles[idx][2].coord.y = (float)(1.f * coord.y);
	grid->triangles[idx][2].coord.z =
		(float)vertmap[coord.y][coord.x + 1].coord.z * 0.15f;
	grid->triangles[idx][0].coord.x = (float)(1.f * coord.x);
	grid->triangles[idx][0].coord.y = (float)(1.f * coord.y);
	grid->triangles[idx][0].coord.z =
		(float)vertmap[coord.y][coord.x].coord.z * 0.15f;
}

static void		top_right_triangle_colors(t_grid *grid, size_t idx,
											t_vert **vertmap, t_vec2 coord)
{
	grid->triangles[idx][0].color = vertmap[coord.y + 1][coord.x + 1].color;
	grid->triangles[idx][1].color.r = 1;
	grid->triangles[idx][1].color.g = 1;
	grid->triangles[idx][1].color.b = 1;
	grid->triangles[idx][1].color = vertmap[coord.y][coord.x].color;
	grid->triangles[idx][2].color = vertmap[coord.y + 1][coord.x].color;
}

static void		bottom_left_triangle_colors(t_grid *grid, size_t idx,
											t_vert **vertmap, t_vec2 coord)
{
	grid->triangles[idx][1].color = vertmap[coord.y + 1][coord.x + 1].color;
	grid->triangles[idx][2].color = vertmap[coord.y][coord.x + 1].color;
	grid->triangles[idx][0].color.r = 1;
	grid->triangles[idx][0].color.g = 1;
	grid->triangles[idx][0].color.b = 1;
	grid->triangles[idx][0].color = vertmap[coord.y][coord.x].color;
}

/*
**	Triangles must be constructed counter-clockwise, by convention
*/

void			init_grid_from_vertmap(t_grid *grid, t_vert **vertmap,
										int width, int height)
{
	t_vec2		coord;
	size_t		i;

	i = 0;
	coord.x = 0;
	grid->width = width;
	grid->height = height;
	if (!(grid->triangles = (t_tri *)ft_memalloc(sizeof(t_tri)
												* width * height * 2)))
		alloc_error("grid->triangles", sizeof(t_tri) * width * height * 2);
	while (coord.x < width)
	{
		coord.y = 0;
		while (coord.y < height)
		{
			top_right_triangle_colors(grid, i, vertmap, coord);
			top_right_triangle_vertices(grid, i, vertmap, coord);
			bottom_left_triangle_colors(grid, i + 1, vertmap, coord);
			bottom_left_triangle_vertices(grid, i + 1, vertmap, coord);
			i += 2;
			coord.y++;
		}
		coord.x++;
	}
}
