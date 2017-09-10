/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 15:34:06 by tdefresn          #+#    #+#             */
/*   Updated: 2017/09/10 23:08:52 by mouton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glfw.h"

/*
** README
** ------
**
** Signature is imposed by GLFW, we have no control on the number of
** arguments. According to 42 staff, it is not cheating.
** (see: https://forum.intra.42.fr/topics/1858/messages?page=1#13658)
*/

void	key_callback(GLFWwindow *win, int key, int code, int action, int mods)
{
	(void)mods;
	(void)code;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(win, GLFW_TRUE);
}
