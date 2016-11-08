/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 13:40:58 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/08 14:51:47 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	new_canvas(t_mlx_st *mlx, t_vec2 size)
{
	t_image		*can;

	if (!(can = (t_image *)ft_memalloc(sizeof(t_image))))
		alloc_error("can", sizeof(t_image));
	can->width = size.x;
	can->height = size.y;
	if (!(can->img = mlx_new_image(mlx->sess, can->width, can->height)))
		alloc_error("can->img", sizeof(int) * can->width * can->height);
	can->data = mlx_get_data_addr(can->img, &can->bpp, &can->sl, &can->endian);
	can->aspect = (double)can->width / (double)can->height;
	mlx->canvas = can;
}
