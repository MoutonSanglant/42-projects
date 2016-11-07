/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_sess.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 12:20:34 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/07 19:49:07 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
**	return
**	1: system is big-endian
**	0: system is little-endian
*/

static int	get_system_endian(void)
{
	int		a;

	a = 0x11223344;
	if (((unsigned char *)&a)[0] == 0x11)
		return (1);
	return (0);
}

void		init_mlx_sess(t_mlx_st *mlx)
{
	ft_bzero(mlx, sizeof(t_mlx_st));
	mlx->name = ft_strdup("Fract'ol");
	mlx->viewport.zoom_level = 1.f;
	mlx->viewport.size.x = 2.f;
	mlx->viewport.size.y = 2.f;
	mlx->need_update = 1;
	mlx->system_endian = get_system_endian();
	mlx->settings.tooltip = 0;
	if (!(mlx->sess = mlx_init()))
		error("Can't create mlx session");
}
