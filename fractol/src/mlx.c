/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 13:20:59 by tdefresn          #+#    #+#             */
/*   Updated: 2016/12/06 16:23:15 by tdefresn         ###   ########.fr       */
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

static int	close_button(int e, void *p)
{
	(void)e;
	(void)p;
	exit(0);
	return (0);
}

void		destroy_mlx_sess(t_mlx_st *mlx)
{
	mlx_destroy_image(mlx->sess, mlx->canvas->img);
	mlx_destroy_window(mlx->sess, mlx->win);
	ft_memdel((void **)&mlx->canvas);
	ft_memdel((void **)&mlx->sess);
	ft_memdel((void **)&mlx->name);
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
	mlx->settings.draw_gui = 1;
	if (!(mlx->sess = mlx_init()))
		error("Can't create mlx session");
}

void		start_mlx_sess(t_mlx_st *mlx)
{
	mlx_hook(mlx->win, DESTROYNOTIFY, 0, &close_button, (void *)mlx);
	mlx_hook(mlx->win, KEYPRESS, KEYPRESSMASK, &keypress, (void *)mlx);
	mlx_hook(mlx->win, KEYRELEASE, KEYRELEASEMASK, &keyrelease, (void *)mlx);
	mlx_hook(mlx->win, MOTIONNOTIFY, POINTERMOTIONMASK,
										&mouse_motion_event, (void *)mlx);
	mlx_mouse_hook(mlx->win, &mouse_click_event, (void *)mlx);
	mlx_expose_hook(mlx->win, &expose, (void *)mlx);
	mlx_loop_hook(mlx->sess, &draw_loop, (void *)mlx);
	mlx_loop(mlx->sess);
}
