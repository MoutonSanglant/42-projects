/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 18:18:01 by tdefresn          #+#    #+#             */
/*   Updated: 2017/09/10 23:49:13 by mouton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "errors.h"

// Si
// Shadow rays
// - sent toward light sources
// - determine if ray intersect objects
// Ri
// Reflected rays
// - if surface is reflective, ray is projected as reflected ray
// Ti
// Transmitted rays
//
// ray live until scene end or max recursion level reached
//
// ray:
// R0: origin
// Rd: direction
typedef struct	s_ray
{
	t_vec3f	origin;
	t_vec3f	direction;

}				t_ray;

// solution of Quadratic equation:
// normal way:
// x = [-b (+/-)(b2 - 4ac).5]/2a
// may give numerical error if a or c is small
// better way:
// q = -0.5 [b + sgn(b) (b2 - 4ac).5]
// then x1 = q/a; x2 =c/q;

// * ray generated for each pixel
//


void	rt_render(void *context)
{
	(void)context;
}

int		main(int argc, const char **argv)
{
	t_context			context;
	t_glfw_parameters	glfw_parameters;

	ft_bzero(&context, sizeof(t_context));
	context.size.x = WINDOW_WIDTH;
	context.size.y = WINDOW_HEIGHT;
	/*
	context.render_fn = &rt_render;
	*/

	if (argc < 1 || get_arguments(argc, argv, &context))
		error (ERRNO_USAGE, NULL);
	glfw_parameters.title = WINDOW_TITLE;
	glfw_parameters.width = context.size.x;
	glfw_parameters.height = context.size.y;
	glfw_parameters.render_fn = &rt_render;
	glfw_parameters.context = &context;
	// We are loading the scene after the graphic libary is loaded
	// since we will load scene dynamicaly
	// Load the scene
	load_scene(FILE_SCENE_EXAMPLE);
	// Set the scene
	if (!(glfw_window_init(&glfw_parameters)))
		return (1);
	return (0);
}
