/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouton </var/spool/mail/mouton>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 21:51:07 by mouton            #+#    #+#             */
/*   Updated: 2017/09/12 21:51:07 by mouton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORM_H
# define TRANSFORM_H

# include "math/vector.h"

typedef int		t_id;

typedef struct s_transform	t_transform;

typedef enum	e_geometry_type
{
	GEOMETRY_TYPE_PLANE,
	GEOMETRY_TYPE_SPHERE,
	GEOMETRY_TYPE_CUBE,
	GEOMETRY_TYPE_UNKNOWN,
}				t_geometry_type;

struct			s_transform
{
	t_transform		*children;
	void			*object;
	char			*name;
	t_id			id;
	t_geometry_type	type;
	t_vec3f			location;
	t_vec4f			rotation;
	t_vec3f			scale;
};


/*
typedef struct	s_plane
{
}				t_plane;

typedef struct	s_sphere
{
}				t_sphere;

typedef struct	s_cube
{
}				t_cube;
*/


t_transform		*new_transform(t_geometry_type type, t_vec3f *location);

#endif
