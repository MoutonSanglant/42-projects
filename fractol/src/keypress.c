/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 14:14:47 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/03 02:45:18 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	loop_colorschemes(t_fractol_st *fractol, int modifier)
{
	static int	scheme = 0;

	if (modifier)
		scheme--;
	else
		scheme++;
	if (scheme > 7)
		scheme = 0;
	else if (scheme < 0)
		scheme = 7;
	set_color_scheme(fractol, scheme);
}

static void	fractol_shift_events(int key, t_fractol_st *fractol)
{
	//ft_printf("key: %i; star: %i\n", key, KEY_STAR);
	if (key == KEY_H)
		fractol->hue += 0.01f;
	else if (key == KEY_S)
		fractol->saturation += 0.01f;
	else if (key == KEY_L)
		fractol->lightness += 0.01f;
	else if (key == KEY_TAB)
		loop_colorschemes(fractol, 1);
	else if (key == KEY_STAR)
		fractol->max_iterations +=
			(fractol->max_iterations < MAX_ITERATIONS - 1) ? 1 : 0;
	fractol->hue = (fractol->hue > 1) ? 1 : fractol->hue;
	fractol->saturation = (fractol->saturation > 1) ? 1 : fractol->saturation;
	fractol->lightness = (fractol->lightness > 1) ? 1 : fractol->lightness;
}

static void	fractol_ctrl_events(int key, t_fractol_st *fractol)
{
	if (key == KEY_H)
		fractol->hue -= 0.01f;
	else if (key == KEY_S)
		fractol->saturation -= 0.01f;
	else if (key == KEY_L)
		fractol->lightness -= 0.01f;
	fractol->hue = (fractol->hue < 0) ? 0 : fractol->hue;
	fractol->saturation = (fractol->saturation < 0) ? 0 : fractol->saturation;
	fractol->lightness = (fractol->lightness < 0) ? 0 : fractol->lightness;
}

static void	fractol_events(int key, t_fractol_st *fractol)
{
	if (key == KEY_H)
		fractol->damp_hue = (fractol->damp_hue) ? 0 : 1;
	else if (key == KEY_S)
		fractol->damp_saturation = (fractol->damp_saturation) ? 0 : 1;
	else if (key == KEY_L)
		fractol->damp_lightness = (fractol->damp_lightness) ? 0 : 1;
	else if (key == KEY_NUMPAD_STAR)
		fractol->max_iterations +=
			(fractol->max_iterations < MAX_ITERATIONS - 1) ? 1 : 0;
	else if (key == KEY_NUMPAD_SLASH)
		fractol->max_iterations -=
			(fractol->max_iterations > 0) ? 1 : 0;
	else if (key == KEY_TAB)
		loop_colorschemes(fractol, 0);
}

int			keypress(int key, void *p)
{
	t_mlx_st	*mlx;
	int			color;

	mlx = (t_mlx_st *)p;
	mlx->need_update = 1;
	ft_printf("key: %i\n", key);
	if (key == KEY_NUMPAD_MORE || key == 44)
		zoom_in(mlx, 0, 0);
	else if (key == KEY_NUMPAD_LESS || key == 47)
		zoom_out(mlx, 0, 0);
	else if (key == KEY_LEFT)
		mlx->viewport.pos.x -= .1f / mlx->viewport.zoom_level;
	else if (key == KEY_RIGHT)
		mlx->viewport.pos.x += .1f / mlx->viewport.zoom_level;
	else if (key == KEY_UP)
		mlx->viewport.pos.y -= .1f / mlx->viewport.zoom_level;
	else if (key == KEY_DOWN)
		mlx->viewport.pos.y += .1f / mlx->viewport.zoom_level;
	else if (key == KEY_R)
		((t_fractol_st *)mlx->datas)->color.r += .3f;
	else if (key == KEY_G)
		((t_fractol_st *)mlx->datas)->color.g += .3f;
	else if (key == KEY_B)
		((t_fractol_st *)mlx->datas)->color.b += .3f;
	else if (key == KEY_I)
	{
		color = mlx->options.faces_color;
		mlx->options.faces_color = mlx->options.lines_color;
		mlx->options.lines_color = color;
	}
	else if (key == KEY_LEFT_SHIFT || key == KEY_RIGHT_SHIFT)
		mlx->modifiers.shift = 1;
	else if (key == KEY_LEFT_CTRL || key == KEY_RIGHT_CTRL)
		mlx->modifiers.ctrl = 1;
	else if (mlx->modifiers.ctrl)
		fractol_ctrl_events(key, ((t_fractol_st *)mlx->datas));
	else if (mlx->modifiers.shift)
		fractol_shift_events(key, ((t_fractol_st *)mlx->datas));
	else
		fractol_events(key, ((t_fractol_st *)mlx->datas));
	set_viewport(mlx);
	return (0);
}
