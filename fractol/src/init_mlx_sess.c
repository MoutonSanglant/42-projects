/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_st.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 14:39:50 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/04 01:13:36 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
**	World, View & Projection matrices
**	---------------------------------
**		World_To_Camera is the inverse matric of View matrix,
**		it is precomputed to save up process time
**	---------------------------------
**		Camera needs to look down (along the negative 'Z-axis')
*/

static void	init_matrices(t_mlx_st *mlx)
{
	t_mat4x4	trans;

	if (!(mlx->world = (t_mat4x4 *)ft_memalloc(sizeof(t_mat4x4))))
		alloc_error("mlx->world", sizeof(t_mat4x4));
	if (!(mlx->view = (t_mat4x4 *)ft_memalloc(sizeof(t_mat4x4))))
		alloc_error("mlx->view", sizeof(t_mat4x4));
	if (!(mlx->projection = (t_mat4x4 *)ft_memalloc(sizeof(t_mat4x4))))
		alloc_error("mlx->projection", sizeof(t_mat4x4));
	if (!(mlx->world_to_camera = (t_mat4x4 *)ft_memalloc(sizeof(t_mat4x4))))
		alloc_error("mlx->world_to_camera", sizeof(t_mat4x4));
	identity_matrix4(mlx->world);
	identity_matrix4(mlx->view);
	identity_matrix4(mlx->projection);
	identity_matrix4(mlx->world_to_camera);
	rotation_x_matrix4(&trans, RAD(90));
	matrix4_product(&trans, mlx->view);
	inverse_matrix4(mlx->view, mlx->world_to_camera);
}

static void	init_camera(t_mlx_st *mlx)
{
	mlx->camera.aspect = (float)mlx->canvas->width / (float)mlx->canvas->height;
	mlx->camera.angle_of_view = 90.f;
	mlx->camera.near = .1f;
	mlx->camera.far = 100.f;
	mlx->camera.right = .1f * mlx->camera.aspect;
	mlx->camera.top = .1f;
	mlx->camera.left = -mlx->camera.right;
	mlx->camera.bottom = -mlx->camera.top;
}

static void	draw_settings(t_mlx_st *mlx)
{
	mlx->options.tooltip = 1;
	mlx->options.fill_faces = 0;
	mlx->options.line_width = .02f;
	mlx->options.lines_color = 0x00ffffff;
	mlx->options.bg_color = 0x00000000;
	mlx->options.faces_color = mlx->options.bg_color;
}

/*
**	return
**	1: system is big-endian
**	0: system is little-endian
*/

static int	get_system_endian(void)
{
	int		a;

	a = 0x11223344;
	if (((unsigned char *)&a)[0] == 0x11)
		return (1);
	return (0);
}

void		init_mlx_sess(t_mlx_st *mlx)
{
	if (!(mlx->win = mlx_new_window(mlx->sess, mlx->canvas->width,
										mlx->canvas->height, mlx->name)))
	{
		ft_memdel((void **)&mlx);
		alloc_error("mlx->win", sizeof(int) * mlx->canvas->width
											* mlx->canvas->height);
	}
	mlx->need_update = 1;
	mlx->last_tval.tv_sec = 0;
	mlx->last_tval.tv_usec = 0;
	mlx->system_endian = get_system_endian();
	init_matrices(mlx);
	init_camera(mlx);
	draw_settings(mlx);
}
