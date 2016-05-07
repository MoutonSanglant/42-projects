/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_mlx_mlx.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 14:40:41 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/07 20:49:34 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int		close_button(int e, void *p)
{
	(void)e;
	(void)p;
	exit(0);
	return (0);
}

#ifdef BONUS

static void		set_mlx_hooks(t_mlx_st *mlx)
{
	mlx_hook(mlx->win, 17, 0, &close_button, (void *)mlx);
	mlx_hook(mlx->win, KEYPRESS, KEYPRESSMASK, &keydown, (void *)mlx);
	mlx_key_hook(mlx->win, &keypress, (void *)mlx);
	mlx_expose_hook(mlx->win, &expose, (void *)mlx);
	mlx_loop_hook(mlx->sess, &draw_loop, (void *)mlx);
}

#else

static void		set_mlx_hooks(t_mlx_st *mlx)
{
	mlx_key_hook(mlx->win, &keypress, (void *)mlx);
	mlx_expose_hook(mlx->win, &expose, (void *)mlx);
	mlx_loop_hook(mlx->sess, &draw_loop, (void *)mlx);
}

#endif

void			start_mlx_sess(t_mlx_st *mlx)
{
	//camera(mlx, "orthographic");
	set_mlx_hooks(mlx);
	mlx_loop(mlx->sess);
}
