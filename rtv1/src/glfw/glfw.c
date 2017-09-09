/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 16:09:15 by tdefresn          #+#    #+#             */
/*   Updated: 2017/09/09 16:10:58 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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
