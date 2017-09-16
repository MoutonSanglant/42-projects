/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 17:51:44 by tdefresn          #+#    #+#             */
/*   Updated: 2017/03/19 17:51:44 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <stdint.h>

typedef struct	s_vec2
{
	int x;
	int y;
}				t_vec2;

typedef struct	s_vec2u
{
	uint32_t	x;
	uint32_t	y;
}				t_vec2u;

typedef struct	s_vec2f
{
	float		x;
	float		y;
}				t_vec2f;

typedef struct	s_vec3
{
	int x;
	int y;
	int z;
}				t_vec3;

typedef struct	s_vec3u
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	z;
}				t_vec3u;

typedef struct	s_vec3f
{
	float		x;
	float		y;
	float		z;
}				t_vec3f;

typedef struct	s_vec4
{
	int x;
	int y;
	int z;
	int w;
}				t_vec4;

typedef struct	s_vec4u
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	z;
	uint32_t	w;
}				t_vec4u;

typedef struct	s_vec4f
{
	float		x;
	float		y;
	float		z;
	float		w;
}				t_vec4f;

t_vec2 *vec2(t_vec2 *vector, int x, int y);
t_vec3 *vec3(t_vec3 *vector, int x, int y, int z);

t_vec2f *vec2f(t_vec2f *vector, float x, float y);
t_vec3f *vec3f(t_vec3f *vector, float x, float y, float z);

#endif
