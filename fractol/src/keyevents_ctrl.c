/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyevents_ctrl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 17:39:03 by tdefresn          #+#    #+#             */
/*   Updated: 2017/05/14 18:33:49 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	keyevent_char(t_context *ctx, int key)
{
	t_fractol_st	*fractol;

	fractol = ((t_fractol_st *)ctx->datas);
	if (key == KEY_R)
		fractol->color.r -= (fractol->color.r - 3.f < 0) ? 0 : 3.f;
	else if (key == KEY_G)
		fractol->color.g -= (fractol->color.g - 3.f < 0) ? 0 : 3.f;
	else if (key == KEY_B)
		fractol->color.b -= (fractol->color.b - 3.f < 0) ? 0 : 3.f;
	else if (key == KEY_H)
		fractol->hue -= 0.01f;
	else if (key == KEY_S)
		fractol->saturation -= 0.01f;
	else if (key == KEY_L)
		fractol->lightness -= 0.01f;
	fractol->hue = (fractol->hue < 0.01f) ? 0.99f : fractol->hue;
	fractol->saturation = (fractol->saturation < 0) ? 0 : fractol->saturation;
	fractol->lightness = (fractol->lightness < 0) ? 0 : fractol->lightness;
	return (0);
}

int			keyevent_ctrl(t_context *ctx, int key,
								int (exec)(t_context *, const t_key *, int))
{
	static const t_key	key_list[7] = {
		{ KEY_R, &keyevent_char },
		{ KEY_G, &keyevent_char },
		{ KEY_B, &keyevent_char },
		{ KEY_H, &keyevent_char },
		{ KEY_S, &keyevent_char },
		{ KEY_L, &keyevent_char },
		{ 0, NULL }
	};

	return (exec(ctx, key_list, key));
}
