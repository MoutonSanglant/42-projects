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

# include <stdint.h>
# include <math.h>

# include "vector.h"

//typedef t_vec4f	t_mat4x4[4];
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


//void	mat4x4_identity(t_mat4x4 m);
void	mat4x4_identity(t_mat4x4 m);
void	inverse_matrix4(t_mat4x4 m, t_mat4x4 inv_out);

void	copy_matrix4(t_mat4x4 dst, const t_mat4x4 src);
void	mat4x4_ortho(t_mat4x4 m, t_camera *camera);

void	translation_matrix4(t_mat4x4 m, t_vec3f v);
void	scaling_matrix4(t_mat4x4 m, t_vec3f v);
//void	rotation_x_matrix4(t_mat4x4 *m, float alpha);
//void	rotation_y_matrix4(t_mat4x4 *m, float alpha);
//void	rotation_z_matrix4(t_mat4x4 *m, float alpha);
void	mat4x4_rotate_X(t_mat4x4 m, float alpha);
void	mat4x4_rotate_Y(t_mat4x4 m, float alpha);
void	mat4x4_rotate_Z(t_mat4x4 m, float alpha);

void	transpose_matrix4(t_mat4x4 m);
//void	matrix4_product(t_mat4x4 *in, t_mat4x4 *out);
void	mat4x4_mul(t_mat4x4 a, t_mat4x4 b, t_mat4x4 out);
t_vec3f	apply_matrix4(t_vec3f a, t_mat4x4 m);

#endif
