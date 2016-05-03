/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/01 17:29:05 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/03 23:49:19 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		set_perspective_camera(t_mlx_st *mlx)
{
	t_mat4x4	tmp;
	t_vec3f		loc;

	loc.x = 0;
	loc.y = mlx->options.distance;
	loc.z = 0;
	mlx->camera.near = .1f;
	identity_matrix4(mlx->world);
	rotation_z_matrix4(&tmp, RAD(135));
	matrix4_product(&tmp, mlx->world);
	rotation_x_matrix4(&tmp, RAD(-20));
	matrix4_product(&tmp, mlx->world);
	translation_matrix4(&tmp, loc);
	matrix4_product(&tmp, mlx->world);
	perspective_projection_matrix4(mlx->projection, &mlx->camera);
}

static void		set_orthographic_camera(t_mlx_st *mlx)
{
	t_mat4x4	tmp;
	t_vec3f		loc;

	loc.x = 0;
	loc.y = mlx->options.distance * 6;
	loc.z = 0;
	mlx->camera.top = .1f;
	mlx->camera.bottom = -mlx->camera.top;
	mlx->camera.right = .1f * mlx->camera.aspect;
	mlx->camera.left = -mlx->camera.right;
	mlx->camera.near = 1.f;
	identity_matrix4(mlx->world);
	rotation_x_matrix4(&tmp, RAD(-90));
	matrix4_product(&tmp, mlx->world);
	//rotation_z_matrix4(&tmp, RAD(135));
	//matrix4_product(&tmp, mlx->world);
	//rotation_x_matrix4(&tmp, RAD(-20));
	//matrix4_product(&tmp, mlx->world);
	translation_matrix4(&tmp, loc);
	matrix4_product(&tmp, mlx->world);
	orthographic_projection_matrix4(mlx->projection, &mlx->camera);
}

void			camera(t_mlx_st *mlx, char *str)
{
	if (ft_strequ(str, "perspective"))
		set_perspective_camera(mlx);
	else if (ft_strequ(str, "orthographic"))
		set_orthographic_camera(mlx);
	else
	{
		ft_eprintf("Error: incorrect camera format");
		exit(155);
	}
}
