/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouton </var/spool/mail/mouton>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 21:26:02 by mouton            #+#    #+#             */
/*   Updated: 2017/09/12 22:25:38 by mouton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "math/vector.h"

#include "glfw/glfw.h"

/*
** solution of Quadratic equation:
** normal way:
** x = [-b (+/-)(b2 - 4ac).5]/2a
** may give numerical error if a or c is small
** better way:
** q = -0.5 [b + sgn(b) (b2 - 4ac).5]
** then x1 = q/a; x2 =c/q;

** * ray generated for each pixel
*/

void	render(void *context)
{
	(void)context;
	// Compute ray tracing stuff !
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glEnable(GL_SCISSOR_TEST);
	glScissor(10, 20, 80, 30);
	glClearColor(1, 0, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_SCISSOR_TEST);
}
