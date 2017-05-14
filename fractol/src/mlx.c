/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 13:20:59 by tdefresn          #+#    #+#             */
/*   Updated: 2017/05/14 19:05:37 by tdefresn         ###   ########.fr       */
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

static int	close_button(void *p)
{
	destroy_mlx_sess((t_context *)p);
	exit(0);
	return (0);
}

void		destroy_mlx_sess(t_context *ctx)
{
	gpgpu_close(ctx);
	mlx_destroy_image(ctx->sess, ctx->canvas->img);
	mlx_destroy_window(ctx->sess, ctx->win);
	ft_memdel((void **)&ctx->canvas);
	ft_memdel((void **)&ctx->sess);
	ft_memdel((void **)&ctx->name);
}

void		init_mlx_sess(t_context *ctx)
{
	ft_bzero(ctx, sizeof(t_context));
	ctx->name = ft_strdup("Fract'ol");
	ctx->viewport.zoom_level = 1.f;
	ctx->viewport.size.x = 2.f;
	ctx->viewport.size.y = 2.f;
	ctx->need_update = 1;
	ctx->system_endian = get_system_endian();
	ctx->settings.tooltip = 0;
	ctx->settings.draw_gui = 1;
	if (!(ctx->sess = mlx_init()))
		error("Can't create mlx session");
}

void		start_mlx_sess(t_context *ctx)
{
	gpgpu_init(ctx);
	mlx_hook(ctx->win, KEYPRESS, KEYPRESSMASK, &keypress, (void *)ctx);
	mlx_hook(ctx->win, KEYRELEASE, KEYRELEASEMASK, &keyrelease, (void *)ctx);
	mlx_hook(ctx->win, DESTROYNOTIFY, 0, &close_button, (void *)ctx);
	mlx_hook(ctx->win, MOTIONNOTIFY, POINTERMOTIONMASK,
										&mouse_motion_event, (void *)ctx);
	mlx_mouse_hook(ctx->win, &mouse_click_event, (void *)ctx);
	mlx_expose_hook(ctx->win, &expose, (void *)ctx);
	mlx_loop_hook(ctx->sess, &draw_loop, (void *)ctx);
	mlx_loop(ctx->sess);
}
