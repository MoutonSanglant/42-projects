/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color_scheme.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 22:20:40 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/03 23:59:37 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	set_color_scheme(t_mlx_st *mlx, int lines_color,
							int faces_color, int bg_color)
{
	mlx->options.lines_color = lines_color;
	mlx->options.faces_color = faces_color;
	mlx->options.bg_color = bg_color;
}
