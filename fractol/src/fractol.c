/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 14:15:11 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/08 02:09:59 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_fractol(t_fractol_st *fractol)
{
	ft_bzero(fractol, sizeof(t_fractol_st));
	ft_memset(&fractol->color, 1, sizeof(t_color));
	fractol->iterations = 50;
	fractol->color.r = 255.f;
	fractol->color.g = 255.f;
	fractol->color.b = 255.f;
	fractol->hue = .5f;
	fractol->saturation = 1.f;
	fractol->lightness = .5f;
	fractol->damp_hue = 1;
	fractol->damp_saturation = 1;
	fractol->damp_lightness = 1;
	set_colorscheme(fractol, 0);
}
