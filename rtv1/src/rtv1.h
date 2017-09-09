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

# define WINDOW_TITLE "RTv1"
# define WINDOW_WIDTH	640
# define WINDOW_HEIGHT	480

# define FILE_SCENE_EXAMPLE "resources/scenes/example.rt"

typedef struct	s_context
{
	t_vec2 size;
}				t_context;

typedef enum	e_trans_type
{
	TRANS_TYPE_PLANE,
	TRANS_TYPE_SPHERE
}				t_trans_type;

typedef struct	s_trans
{
//	void			*object;
	t_trans_type	type;
	t_vec3f			location;
	t_vec4f			rotation;
	t_vec3f			scale;
}				t_trans;

/*
typedef struct	s_plane
{
}				t_plane;
*/

/*
** == arguments.c
*/

int			get_arguments(int argc, const char **argv, t_context *context);

/*
** == arguments_window.c
*/

int	parse_argument_width(const char *arg, void *user_data);
int	parse_argument_height(const char *arg, void *user_data);

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
