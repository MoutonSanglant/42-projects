/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 14:43:09 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/06 14:50:22 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	new_window(t_mlx_st *mlx, t_vec2 size)
{
	if (!(mlx->win = mlx_new_window(mlx->sess, size.x, size.y, mlx->name)))
		alloc_error("new_window: mlx->win", sizeof(int) * size.x * size.y);
}
