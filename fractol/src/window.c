/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 14:43:09 by tdefresn          #+#    #+#             */
/*   Updated: 2017/05/14 18:29:02 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	new_window(t_context *ctx, t_vec2 size)
{
	if (!(ctx->win = mlx_new_window(ctx->sess, size.x, size.y, ctx->name)))
		alloc_error("new_window: ctx->win", sizeof(int) * size.x * size.y);
}
