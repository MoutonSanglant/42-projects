/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keydown.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 14:03:16 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/30 10:20:05 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
static void	rotate_around_center(t_mlx_st *mlx, char c, int dir)
{
	t_mat4x4	m_iworld;
	t_mat4x4	m_rot;

	inverse_matrix4(mlx->world, &m_iworld);
	identity_matrix4(&m_rot);
	if (c == 'z')
		rotation_z_matrix4(&m_rot, RAD(3 * dir));
	else if (c == 'y')
		rotation_y_matrix4(&m_rot, RAD(3 * dir));
	else if (c == 'x')
		rotation_x_matrix4(&m_rot, RAD(3 * dir));
	matrix4_product(&m_rot, &m_iworld);
	inverse_matrix4(&m_iworld, mlx->world);
}

static void	translation_events(t_mlx_st *mlx, int key)
{
	t_mat4x4	m_loc;
	t_vec3f		loc;

	loc.x = 0;
	loc.y = 0;
	loc.z = 0;
	identity_matrix4(&m_loc);
	if (key == KEY_NUMPAD_MORE)
		mlx->viewport.zoom_level *= 2.f;
		//loc.y = -1 * mlx->options.distance;
	else if (key == KEY_NUMPAD_LESS)
		mlx->viewport.zoom_level *= .5f;
		//loc.y = 1 * mlx->options.distance;
	else if (key == KEY_LEFT)
		loc.x = -1;
	else if (key == KEY_RIGHT)
		loc.x = 1;
	else if (key == KEY_UP)
		loc.z = -1;
	else if (key == KEY_DOWN)
		loc.z = 1;
	else if (key == KEY_PAGE_UP)
		change_grid_z(mlx->grid, 1.1f);
	else if (key == KEY_PAGE_DOWN)
		change_grid_z(mlx->grid, 0.9f);
	translation_matrix4(&m_loc, loc);
	matrix4_product(&m_loc, mlx->world);
}

static void	matrix_events(t_mlx_st *mlx, int key)
{
	if (key == KEY_O)
		camera(mlx, "orthographic");
	else if (key == KEY_P)
		camera(mlx, "perspective");
	else if (key == KEY_Q)
		rotate_around_center(mlx, 'y', 1);
	else if (key == KEY_E)
		rotate_around_center(mlx, 'y', -1);
	else if (key == KEY_A)
		rotate_around_center(mlx, 'z', -1);
	else if (key == KEY_D)
		rotate_around_center(mlx, 'z', 1);
	else if (key == KEY_W)
		rotate_around_center(mlx, 'x', -1);
	else if (key == KEY_S)
		rotate_around_center(mlx, 'x', 1);
	else
		translation_events(mlx, key);
}

static void	color_events(t_mlx_st *mlx, int key)
{
	if (key == KEY_0)
		set_color_scheme(mlx, 0x00ffffff, 0x00000000, 0x00000000);
	else if (key == KEY_1)
		set_color_scheme(mlx, 0x00ff0000, 0x000000ff, 0x000000ff);
	else if (key == KEY_2)
		set_color_scheme(mlx, 0x00883333, 0x000000ff, 0x0000ff00);
	else if (key == KEY_3)
		set_color_scheme(mlx, 0x00000000, 0x00046000, 0x000460ff);
	else if (key == KEY_4)
		set_color_scheme(mlx, 0x00a34f89, 0x0009af39, 0x00394f90);
	else if (key == KEY_F)
		mlx->options.fill_faces = (mlx->options.fill_faces) ? 0 : 1;
}
*/

static void	loop_colorschemes(t_fractol_st *fractol)
{
	static int	scheme = 0;

	scheme++;
	if (scheme > 7)
		scheme = 0;
	if (scheme == 0)
		fractol->color_fn = &colorset_parametric_hsl;
	else if (scheme == 1)
		fractol->color_fn = &colorset_burning;
	else if (scheme == 2)
		fractol->color_fn = &colorset_deepblue;
	else if (scheme == 3)
		fractol->color_fn = &colorset_smooth;
	else if (scheme == 4)
		fractol->color_fn = &colorset_prismatic;
	else if (scheme == 5)
		fractol->color_fn = &colorset_parametric;
	else if (scheme == 6)
		fractol->color_fn = &colorset_square;
	else if (scheme == 7)
		fractol->color_fn = &colorset_psycho;
}

static void	fractol_events(t_mlx_st *mlx, int key, t_fractol_st *fractol)
{
	(void)mlx;
	if (key == KEY_H)
		fractol->damp_hue = (fractol->damp_hue) ? 0 : 1;
	else if (key == KEY_S)
		fractol->damp_saturation = (fractol->damp_saturation) ? 0 : 1;
	else if (key == KEY_L)
		fractol->damp_lightness = (fractol->damp_lightness) ? 0 : 1;
	else if (key == KEY_TAB)
		loop_colorschemes(fractol);
	else if (key == KEY_NUMPAD_STAR)
		fractol->max_iterations +=
			(fractol->max_iterations < MAX_ITERATIONS - 1) ? 1 : 0;
	else if (key == KEY_NUMPAD_SLASH)
		fractol->max_iterations -=
			(fractol->max_iterations > 0) ? 1 : 0;
}

int			keydown(int key, void *p)
{
	t_mlx_st	*mlx;
	int			color;

	mlx = (t_mlx_st *)p;
	mlx->need_update = 1;
	if (key == KEY_NUMPAD_MORE || key == 44)
		mlx->viewport.zoom_level *= 2.f;
	else if (key == KEY_NUMPAD_LESS || key == 47)
		mlx->viewport.zoom_level *= .5f;
	else if (key == KEY_LEFT)
		mlx->viewport.pos.x -= .1f / mlx->viewport.zoom_level;
	else if (key == KEY_RIGHT)
		mlx->viewport.pos.x += .1f / mlx->viewport.zoom_level;
	else if (key == KEY_UP)
		mlx->viewport.pos.y -= .1f / mlx->viewport.zoom_level;
	else if (key == KEY_DOWN)
		mlx->viewport.pos.y += .1f / mlx->viewport.zoom_level;
	else if (key == KEY_R)
		((t_fractol_st *)mlx->datas)->color.r += .3f;
	else if (key == KEY_G)
		((t_fractol_st *)mlx->datas)->color.g += .3f;
	else if (key == KEY_B)
		((t_fractol_st *)mlx->datas)->color.b += .3f;
	else if (key == KEY_I)
	{
		color = mlx->options.faces_color;
		mlx->options.faces_color = mlx->options.lines_color;
		mlx->options.lines_color = color;
	}
	else
		fractol_events(mlx, key, ((t_fractol_st *)mlx->datas));
	return (0);
}
