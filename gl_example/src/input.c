/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 15:34:06 by tdefresn          #+#    #+#             */
/*   Updated: 2017/03/18 15:49:09 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Function is 5 arguments long, yet the signature is imposed by GLFW
** and I have no control on it thus it shouldn't be considered as cheat.
** Question has been answered by staff members.
** (see: https://forum.intra.42.fr/topics/1858/messages?page=1#13658)
*/

void	key_callback(GLFWwindow *win, int key, int code, int action, int mods)
{
	(void)mods;
	(void)code;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(win, GLFW_TRUE);
}
