/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyvents_shift.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 17:42:17 by tdefresn          #+#    #+#             */
/*   Updated: 2017/05/14 18:33:57 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	keyevent_char(t_context *ctx, int key)
{
	t_fractol_st	*fractol;

	fractol = ((t_fractol_st *)ctx->datas);
	if (key == KEY_H)
		fractol->hue += 0.01f;
	else if (key == KEY_S)
		fractol->saturation += 0.01f;
	else if (key == KEY_L)
		fractol->lightness += 0.01f;
	else if (key == KEY_TAB)
		loop_colorschemes(fractol, 1);
	else if (key == KEY_STAR)
		fractol->iterations +=
			(fractol->iterations < MAX_ITERATIONS - 1) ? 1 : 0;
	else if (key == KEY_SLASH)
		ctx->settings.tooltip = (ctx->settings.tooltip) ? 0 : 1;
	fractol->hue = (fractol->hue > 0.99f) ? 0.01f : fractol->hue;
	fractol->saturation = (fractol->saturation > 1) ? 1 : fractol->saturation;
	fractol->lightness = (fractol->lightness > 1) ? 1 : fractol->lightness;
	return (0);
}

int			keyevent_shift(t_context *ctx, int key,
									int (exec)(t_context *, const t_key *, int))
{
	static const t_key	key_list[7] = {
		{ KEY_H, &keyevent_char },
		{ KEY_S, &keyevent_char },
		{ KEY_L, &keyevent_char },
		{ KEY_TAB, &keyevent_char },
		{ KEY_STAR, &keyevent_char },
		{ KEY_SLASH, &keyevent_char },
		{ 0, NULL }
	};

	return (exec(ctx, key_list, key));
}
