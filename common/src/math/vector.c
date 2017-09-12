/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouton </var/spool/mail/mouton>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 22:38:33 by mouton            #+#    #+#             */
/*   Updated: 2017/09/12 22:51:15 by mouton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void vec2(t_vec2 *vector, int x, int y)
{
	vector->x = x;
	vector->y = y;
}

void vec3(t_vec3 *vector, int x, int y, int z)
{
	vector->x = x;
	vector->y = y;
	vector->z = z;
}

void vec2f(t_vec2f *vector, float x, float y)
{
	vector->x = x;
	vector->y = y;
}

void vec3f(t_vec3f *vector, float x, float y, float z)
{
	vector->x = x;
	vector->y = y;
	vector->z = z;
}

