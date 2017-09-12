/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 16:09:15 by tdefresn          #+#    #+#             */
/*   Updated: 2017/09/12 21:27:29 by mouton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glfw.h"

#include <libftprintf.h>

/*
#ifdef linux

void set_context()
{
	cl_context_properties properties[] = {
		CL_GL_CONTEXT_KHR, (cl_context_properties) glXGetCurrentContext(),
		CL_GLX_DISPLAY_KHR, (cl_context_properties) glXGetCurrentDisplay(),
		CL_CONTEXT_PLATFORM, (cl_context_properties) platform,
		0
	};
}

#elif defined _WIN32

void set_context()
{
	cl_context_properties properties[] = {
		CL_GL_CONTEXT_KHR, (cl_context_properties) wglGetCurrentContext(),
		CL_WGL_HDC_KHR, (cl_context_properties) wglGetCurrentDC(),
		CL_CONTEXT_PLATFORM, (cl_context_properties) platform,
		0
	};
}

#elif defined TARGET_OS_MAC

void set_context()
{
	CGLContextObj glContext = CGLGetCurrentContext();
	CGLShareGroupObj shareGroup = CGLGetShareGroup(glContext);
	cl_context_properties properties[] = {
		CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE,
		(cl_context_properties)shareGroup,
		0
	};
}
#endif

void context()
{
	set_context();
	context = clCreateContext(properties, numDevices, devices, func, usr_data, &err);
}
*/

/*
	const char	*version;
	version = glfwGetVersionString();
	ft_printf("GLFW %s\n", version);
	//glfwWindowHint(GLFW_SAMPLES, 4);
	//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
*/

static
void	render(GLFWwindow *win, t_glfw_parameters *parameters)
{
	glfw_render_fn	render_fn = parameters->render_fn;
	void			*context = parameters->context;

	while (!glfwWindowShouldClose(win))
	{
		int			width;
		int			height;

		glfwGetFramebufferSize(win, &width, &height);

		render_fn(context);
		// Trace rays
		// t_ray

		glfwSwapBuffers(win);
		glfwWaitEvents();
	}
}

static
void		error_glfw(int error, const char *description)
{
	ft_eprintf("Error %i: %s\n", error, description);
}

static
int		init_glew()
{
	GLenum err = glewInit();

	if (err != GLEW_OK)
	{
		ft_eprintf("Error: %s\n", glewGetErrorString(err));
		return (0);
	}
	ft_printf("GLEW %s\n", glewGetString(GLEW_VERSION));
	return (1);
}

GLFWwindow		*glfw_window_init(t_glfw_parameters *parameters)
{
	GLFWwindow	*win;

	glfwSetErrorCallback((GLFWerrorfun)error_glfw);
	if (!glfwInit())
	{
		ft_printf(GLFW_INIT);
		return (NULL);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	if (!(win = glfwCreateWindow(parameters->width, parameters->height, parameters->title, NULL, NULL)))
	{
		glfwTerminate();
		return (NULL);
	}
	glfwMakeContextCurrent(win);
	if (!init_glew())
	{
		glfwTerminate();
		return (NULL);
	}
	glfwSwapInterval(1);
	ft_printf("OpenGL %s\n", (char *)glGetString(GL_VERSION));
	glfwSetKeyCallback(win, key_callback);
	render(win, parameters);
	glfwTerminate();
	return (win);
}
