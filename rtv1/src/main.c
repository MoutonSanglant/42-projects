/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 18:18:01 by tdefresn          #+#    #+#             */
/*   Updated: 2017/09/15 22:08:36 by mouton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "errors.h"
#include "render.h"
#include "scene.h"

#include "cl/cl.h"

int		main(int argc, const char **argv)
{
	t_context			context;
	t_glfw_parameters	glfw_parameters;

	ft_bzero(&context, sizeof(t_context));
	vec2(&context.window.size, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (argc < 1 || get_arguments(argc, argv, &context))
		error (ERRNO_USAGE, NULL);
	glfw_parameters.title = WINDOW_TITLE;
	glfw_parameters.width = context.window.size.x;
	glfw_parameters.height = context.window.size.y;
	glfw_parameters.render_fn = &render;
	glfw_parameters.context = &context;
	// Create a new scene from file
	new_scene(FILE_SCENE_EXAMPLE);

	(void)glfw_parameters;
	t_gpgpu_handler gpgpu = NULL;
	gpgpu = cl_init(context.window.size.x, context.window.size.y);
	(void)gpgpu;
	//cl_init(&gpgpu, context.window.size.x, context.window.size.y);
	//if (!(glfw_window_init(&glfw_parameters)))
	//	return (1);
	return (0);
}
