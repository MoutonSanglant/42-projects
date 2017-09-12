/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 19:52:38 by tdefresn          #+#    #+#             */
/*   Updated: 2017/09/12 22:51:42 by mouton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "transform.h"
#include "errors.h"

#include <libft.h>

t_transform		*new_transform(t_geometry_type type, t_vec3f *location)
{
	t_transform		*transform;

	if (!(transform = (t_transform *)ft_memalloc(sizeof(t_transform))))
		error(ERRNO_MEMORY, "new_transform");
	transform->type = type;
	ft_memcpy(&transform->location, location, sizeof(t_vec3f));
	return (transform);
}
