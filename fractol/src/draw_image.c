/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 16:54:03 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/04 00:35:05 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	draw_image(t_mlx_st *mlx, void *img, int *x, int *y)
{
	mlx_put_image_to_window(mlx->sess, mlx->win, img, *x, *y);
}
