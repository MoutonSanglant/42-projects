/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 14:14:47 by tdefresn          #+#    #+#             */
/*   Updated: 2017/05/14 18:33:16 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	exec_keyevent(t_context *ctx, const t_key *key_list, int key)
{
	int		i;

	i = 0;
	while (key_list[i].fn != NULL)
	{
		if (key == key_list[i].code)
			key_list[i].fn(ctx, key);
		i++;
	}
	ctx->need_update = 1;
	return (1);
}

int			keypress(int key, void *p)
{
	t_context	*ctx;

	ctx = (t_context *)p;
	ctx->key_modifiers |= (key == KEY_LEFT_SHIFT || key == KEY_RIGHT_SHIFT)
		? KEY_MODIFIER_SHIFT : 0;
	ctx->key_modifiers |= (key == KEY_LEFT_CTRL || key == KEY_RIGHT_CTRL)
		? KEY_MODIFIER_CTRL : 0;
	if (ctx->key_modifiers & KEY_MODIFIER_CTRL)
		return (keyevent_ctrl(ctx, key, &exec_keyevent));
	else if (ctx->key_modifiers & KEY_MODIFIER_SHIFT)
		return (keyevent_shift(ctx, key, &exec_keyevent));
	else
		return (keyevent(ctx, key, &exec_keyevent));
	return (0);
}
