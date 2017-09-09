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

# include <libftprintf.h>

# include <GLFW/glfw3.h>

# define GLFW_INIT "Cannot initialize GLFW\n"

GLFWwindow	*glfw_window_init(int width, int height, const char *title);

#endif
