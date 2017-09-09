/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 18:17:53 by tdefresn          #+#    #+#             */
/*   Updated: 2017/03/17 18:17:53 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <libft.h>
# include <libftprintf.h>

# include <GL/glew.h>
# include <GLFW/glfw3.h>

# include "options.h"

# include "math/vector.h"
# include "math/matrix.h"

# define OPTIONS_COUNT 3

# define WIN_WIDTH	640
# define WIN_HEIGHT	480

# define ERRNO_USAGE	0x1
# define ERRNO_COLOR	0x2
# define ERRNO_MEMORY	0x3
# define ERRNO_OPEN		0x4
# define ERRNO_READ		0x5

# define ERR_COLOR "invalid color"
# define ERR_MEMORY "memory allocation error (%s)\n"
# define ERR_OPEN "Cannot open file '%s'"
# define ERR_READ "Read error"
# define ERR_UNDEFINED "undefined error"

# define STR_USAGE "rtv1 [-w width] [-h height]\n"

# define FILE_SCENE_EXAMPLE "resources/scenes/example.rt"

typedef struct	s_rt
{
//	t_flags	flags;
	int		width;
	int		height;
}				t_rt;

typedef enum	e_trans_type
{
	TRANS_TYPE_PLANE,
	TRANS_TYPE_SPHERE
}				t_trans_type;

typedef struct	s_trans
{
//	void			*object;
	t_trans_type	type;
	t_vec3f			pos;
	t_vec4f			rot;
	t_vec3f			scale;
}				t_trans;

/*
typedef struct	s_plane
{
}				t_plane;
*/

/*
** == errors.c
*/

void		error(int error, const char *description);
void		error_glfw(int error, const char *description);

/*
** == options.c
*/

//void		match_options(char *arg, t_flags *flags);

/*
** == arguments.c
*/

void		parse_arguments(int count, char **arguments, t_rt *rt);

/*
** == input.c
*/

void		key_callback(GLFWwindow *win, int key, int code, int action, int mods);


/*
** == scene.c
*/
void		load_scene(const char *path);

/*
** == transform.c
*/

t_trans		*new_transform(t_vec3f pos, t_trans_type type);

//t_plane		*new_plane(t_vec3 pos);
//t_sphere	*new_sphere(t_vec3 pos);

#endif
