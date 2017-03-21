/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 19:52:38 by tdefresn          #+#    #+#             */
/*   Updated: 2017/03/21 20:19:57 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_trans		*new_transform(t_vec3f pos, t_trans_type type)
{
	t_trans		*trans;

	if (!(trans = (t_trans *)ft_memalloc(sizeof(t_trans))))
		error(ERRNO_MEMORY, "new_transform");
	trans->type = type;
	trans->pos.x = pos.x;
	trans->pos.y = pos.y;
	trans->pos.z = pos.z;
	return (trans);
}
