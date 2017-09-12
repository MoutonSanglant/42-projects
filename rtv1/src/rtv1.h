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

# include "glfw/glfw.h"
# include "math/matrix.h"

# include "scene.h"

//# include "math/vector.h"

# define WINDOW_TITLE	"RTv1"
# define WINDOW_WIDTH	640
# define WINDOW_HEIGHT	480

# define FILE_SCENE_EXAMPLE "resources/scenes/example.rt"

typedef struct	s_window
{
	t_vec2		size;
}				t_window;

typedef struct	s_context
{
	t_scene			*scene;
	t_window		window;
	glfw_render_fn	*render_fn;
}				t_context;

/*
** == arguments.c
*/

int			get_arguments(int argc, const char **argv, t_context *context);

/*
** == arguments_window.c
*/

int			parse_argument_width(const char *arg, void *user_data);
int			parse_argument_height(const char *arg, void *user_data);

/*
** == render.c
*/

void		render(void *context);

//t_plane		*new_plane(t_vec3 pos);
//t_sphere	*new_sphere(t_vec3 pos);

#endif
