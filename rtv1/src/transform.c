/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 19:52:38 by tdefresn          #+#    #+#             */
/*   Updated: 2017/09/10 00:12:25 by mouton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "errors.h"

t_trans		*new_transform(t_vec3f location, t_trans_type type)
{
	t_trans		*trans;

	if (!(trans = (t_trans *)ft_memalloc(sizeof(t_trans))))
		error(ERRNO_MEMORY, "new_transform");
	trans->type = type;
	trans->location.x = location.x;
	trans->location.y = location.y;
	trans->location.z = location.z;
	return (trans);
}
