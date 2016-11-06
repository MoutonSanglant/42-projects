/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 13:40:58 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/06 19:13:31 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	new_canvas(t_mlx_st *mlx, t_vec2 size)
{
	t_image		*canvas;

	if (!(canvas = (t_image *)ft_memalloc(sizeof(t_image))))
		alloc_error("canvas", sizeof(t_image));
	canvas->width = size.x;
	canvas->height = size.y;
	if (!(canvas->img = mlx_new_image(mlx->sess, canvas->width, canvas->height)))
		alloc_error("canvas->img", sizeof(int) * canvas->width
												* canvas->height);
	canvas->data = mlx_get_data_addr(canvas->img, &canvas->bpp,
										&canvas->sl, &canvas->endian);
	canvas->aspect = (float)canvas->width / (float)canvas->height;
	mlx->canvas = canvas;
}
