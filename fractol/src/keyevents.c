/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyevent.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 17:30:10 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/07 20:16:36 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	keyevent_char(t_mlx_st *mlx, int key)
{
	t_fractol_st	*fractol;

	fractol = ((t_fractol_st *)mlx->datas);
	if (key == KEY_N)
		fractol->negative =  (fractol->negative) ? 0 : 1;
	else if (key == KEY_R)
		fractol->color.r += .3;
	else if (key == KEY_G)
		fractol->color.g += .3;
	else if (key == KEY_B)
		fractol->color.b += .3;
	else if (key == KEY_H)
		fractol->damp_hue = (fractol->damp_hue) ? 0 : 1;
	else if (key == KEY_S)
		fractol->damp_saturation = (fractol->damp_saturation) ? 0 : 1;
	else if (key == KEY_L)
		fractol->damp_lightness = (fractol->damp_lightness) ? 0 : 1;
	else if (key == KEY_NUMPAD_STAR)
		fractol->iterations +=
			(fractol->iterations < MAX_ITERATIONS - 1) ? 1 : 0;
	else if (key == KEY_NUMPAD_SLASH)
		fractol->iterations -= (fractol->iterations > 0) ? 1 : 0;
	else if (key == KEY_TAB)
		loop_colorschemes(fractol, 0);
	return (0);
}

static int	keyevent_zoom(t_mlx_st *mlx, int key)
{
	if (key == KEY_NUMPAD_MORE || key == KEY_MORE)
		zoom_in(mlx, 0, 0);
	else if (key == KEY_NUMPAD_LESS || key == KEY_LESS)
		zoom_out(mlx, 0, 0);
	move_viewport(&mlx->viewport, mlx->canvas);
	return (0);
}

static int	keyevent_arrow(t_mlx_st *mlx, int key)
{
	if (key == KEY_LEFT)
		mlx->viewport.pos.x -= .1 / mlx->viewport.zoom_level;
	else if (key == KEY_RIGHT)
		mlx->viewport.pos.x += .1 / mlx->viewport.zoom_level;
	else if (key == KEY_UP)
		mlx->viewport.pos.y -= .1 / mlx->viewport.zoom_level;
	else if (key == KEY_DOWN)
		mlx->viewport.pos.y += .1 / mlx->viewport.zoom_level;
	move_viewport(&mlx->viewport, mlx->canvas);
	return (0);
}

int			keyevent(t_mlx_st *mlx, int key,
							int (exec)(t_mlx_st *, const t_key *, int))
{
	static const t_key	key_list[19] = {
		{ KEY_NUMPAD_MORE, &keyevent_zoom },
		{ KEY_NUMPAD_LESS, &keyevent_zoom },
		{ KEY_MORE, &keyevent_zoom },
		{ KEY_LESS, &keyevent_zoom },
		{ KEY_LEFT, &keyevent_arrow },
		{ KEY_RIGHT, &keyevent_arrow },
		{ KEY_UP, &keyevent_arrow },
		{ KEY_DOWN, &keyevent_arrow },
		{ KEY_R, &keyevent_char },
		{ KEY_G, &keyevent_char },
		{ KEY_B, &keyevent_char },
		{ KEY_H, &keyevent_char },
		{ KEY_S, &keyevent_char },
		{ KEY_L, &keyevent_char },
		{ KEY_N, &keyevent_char },
		{ KEY_TAB, &keyevent_char },
		{ KEY_NUMPAD_STAR, &keyevent_char },
		{ KEY_NUMPAD_SLASH, &keyevent_char },
		{ 0, NULL }
	};

	return (exec(mlx, key_list, key));
}
