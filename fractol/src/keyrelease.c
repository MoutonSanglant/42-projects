/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyrelease.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/30 14:47:12 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/30 16:19:41 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			keyrelease(int key, void *p)
{
	t_mlx_st	*mlx;

	mlx = (t_mlx_st *)p;
	mlx->need_update = 1;
	if (key == KEY_ESCAPE)
	{
		destroy_mlx_sess(mlx);
		exit(0);
	}
	else if (key == KEY_LEFT_SHIFT || key == KEY_RIGHT_SHIFT)
		mlx->modifiers.shift = 0;
	else if (key == KEY_LEFT_CTRL || key == KEY_RIGHT_CTRL)
		mlx->modifiers.ctrl = 0;
	return (0);
}
