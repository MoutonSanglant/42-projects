/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouton </var/spool/mail/mouton>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 22:13:53 by mouton            #+#    #+#             */
/*   Updated: 2017/09/09 22:13:53 by mouton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLFW_H
# define GLFW_H

# include <GL/glew.h>
# include <GLFW/glfw3.h>

# define GLFW_INIT "Cannot initialize GLFW\n"

typedef void (*glfw_render_fn)(void *context);

typedef struct	s_glfw_parameters
{
	const char		*title;
	int				width;
	int				height;
	glfw_render_fn	render_fn;
	void			*context;
}				t_glfw_parameters;

GLFWwindow	*glfw_window_init(t_glfw_parameters *parameters);

/*
** == input.c
*/

void		key_callback(GLFWwindow *win, int key, int code, int action, int mods);

#endif
