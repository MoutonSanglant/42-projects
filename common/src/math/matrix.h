/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 17:48:51 by tdefresn          #+#    #+#             */
/*   Updated: 2017/03/19 17:48:51 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "vector.h"

# include <math.h>

typedef float	t_mat4x4[16];

typedef struct	s_camera
{
	float	angle_of_view;
	float	aspect;
	float	far;
	float	near;
	float	top;
	float	bottom;
	float	left;
	float	right;
}				t_camera;


void	mat4x4_identity(t_mat4x4 m);
void	mat4x4_inverse(t_mat4x4 m, t_mat4x4 inv_out);

void	mat4x4_copy(t_mat4x4 dst, const t_mat4x4 src);
void	mat4x4_ortho(t_mat4x4 m, t_camera *camera);

void	mat4x4_translate(t_mat4x4 m, t_vec3f v);
void	mat4x4_scale(t_mat4x4 m, t_vec3f v);

void	mat4x4_rotate_x(t_mat4x4 m, float alpha);
void	mat4x4_rotate_y(t_mat4x4 m, float alpha);
void	mat4x4_rotate_z(t_mat4x4 m, float alpha);

void	mat4x4_transpose(t_mat4x4 m);
void	mat4x4_multiply(t_mat4x4 a, t_mat4x4 b, t_mat4x4 out);
t_vec3f	mat4x4_apply(t_vec3f a, t_mat4x4 m);

#endif
