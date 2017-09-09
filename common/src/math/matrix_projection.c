/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_matrix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 18:05:49 by tdefresn          #+#    #+#             */
/*   Updated: 2017/09/09 17:14:54 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

# include <math.h>

/*
**	Perspective projection
**	======================
**	1 0     0       0
**	0 1     0       0
**	0 0 (N + F)/N  -F
**	0 0    1/N      0
**	=================
**	N is Near viewing plane distance
**	F is Far viewing plane distance
*/

void	perspective_mat4x4_projection(t_mat4x4 m, t_camera *camera)
{
	float	scale;
	float	near;
	float	far;

	near = camera->near;
	far = camera->far;
	scale = 1.f / tanf(camera->angle_of_view * .5f * M_PI / 180.f);
	mat4x4_identity(m);
	m[0] = scale / camera->aspect;
	m[5] = scale;
	m[10] = (near + far) / (near - far);
	m[11] = -1.f;
	m[14] = 2.f * far * near / (near - far);
	m[15] = 0.f;
	mat4x4_transpose(m);
}

/*
**	Orthographic projection
**	=======================
**	N is Near viewing plane distance
**	F is Far viewing plane distance
*/

void	mat4x4_ortho(t_mat4x4 m, t_camera *camera)
{
	float	t;
	float	b;
	float	l;
	float	r;

	t = camera->top;
	b = camera->bottom;
	l = camera->left;
	r = camera->right;
	mat4x4_identity(m);
	m[0] = 2.f / (r - l);
	m[3] = -((r + l) / (r - l));
	m[5] = 2.f / (t - b);
	m[7] = -((t + b) / (t - b));
	m[10] = -(2.f / (camera->far - camera->near));
	m[11] = -((camera->far + camera->near) / (camera->far - camera->near));
	m[15] = 1.f;
	mat4x4_transpose(m);
}
