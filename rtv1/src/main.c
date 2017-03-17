/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 18:18:01 by tdefresn          #+#    #+#             */
/*   Updated: 2017/03/17 21:26:57 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

# define WIN_WIDTH 640
# define WIN_HEIGHT 480

int		main(int argc, char **argv)
{
	GLFWwindow *win;

	if (argc < 1)
		return (1);
	(void)argv[0];
	if (!glfwInit())
		ft_printf("Cannot initialize GLFW\n");

	win = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "RTv1", NULL, NULL);
	if (!win)
	{
		glfwTerminate();
		return (1);
	}
	glfwMakeContextCurrent(win);

	while (!glfwWindowShouldClose(win))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(win);
		glfwPollEvents();
	}
	glfwTerminate();
	return (0);
}
