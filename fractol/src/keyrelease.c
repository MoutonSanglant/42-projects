/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyrelease.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 14:47:12 by tdefresn          #+#    #+#             */
/*   Updated: 2017/05/14 18:44:21 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			keyrelease(int key, void *p)
{
	t_context	*ctx;

	ctx = (t_context *)p;
	ctx->need_update = 1;
	if (key == KEY_ESCAPE)
	{
		destroy_mlx_sess(ctx);
		exit(0);
	}
	else if (key == KEY_LEFT_SHIFT || key == KEY_RIGHT_SHIFT)
		ctx->key_modifiers &= ~KEY_MODIFIER_SHIFT;
	else if (key == KEY_LEFT_CTRL || key == KEY_RIGHT_CTRL)
		ctx->key_modifiers &= ~KEY_MODIFIER_CTRL;
	return (0);
}
