/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouton </var/spool/mail/mouton>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 21:50:16 by mouton            #+#    #+#             */
/*   Updated: 2017/09/12 21:50:16 by mouton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "math/vector.h"

/*
** Si
** Shadow rays
** - sent toward light sources
** - determine if ray intersect objects
** Ri
** Reflected rays
** - if surface is reflective, ray is projected as reflected ray
** Ti
** Transmitted rays
**
** ray live until scene end or max recursion level reached
**
** ray:
** R0: origin
** Rd: direction
*/

typedef struct	s_ray
{
	t_vec3f	origin;
	t_vec3f	direction;

}				t_ray;

void		render(void *context);

#endif
