/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorsets_extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 16:13:33 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/06 23:54:28 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		colorset_psycho(int depth, t_fractol_st *fractol)
{
	int		color;
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;

	(void)fractol;
	r =  depth * 13;
	g =  depth * 157;
	b =  depth * 79;
	color = ((int)r << 16) + ((int)g << 8) + b;
	return (color);
}

int		colorset_square(int depth, t_fractol_st *fractol)
{
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;

	(void)fractol;
	r =  depth;
	g =  r * r;
	b =  g * g;
	return (((int)r << 16) + ((int)g << 8) + b);
}

int		colorset_prismatic(int depth, t_fractol_st *fractol)
{
	t_color		rgb;

	rgb = hsl_to_rgb((float)depth/(float)fractol->iterations,
			1.f, (float)depth/(float)fractol->iterations, fractol->negative);
	return ((int)(((int)rgb.r << 16) + ((int)rgb.g << 8) + rgb.b) & 0x00ffffff);
}


int		colorset_parametric(int depth, t_fractol_st *fractol)
{
	t_color		rgb;

	rgb.r = depth * fractol->color.r;
	rgb.g =
		(depth * fractol->color.g > 255) ? 255 : depth * fractol->color.g;
	rgb.b =
		(depth * fractol->color.b > 255) ? 255 : depth * fractol->color.b;
	return (((int)rgb.r << 16) + ((int)rgb.g << 8) + rgb.b);
}

int		colorset_parametric_hsl(int depth, t_fractol_st *fractol)
{
	t_color		rgb;
	float		hue;
	float		saturation;
	float		lightness;

	hue = (fractol->damp_hue) ?
		(float)depth/(float)fractol->iterations : fractol->hue;
	saturation = (fractol->damp_saturation) ?
		(float)depth/(float)fractol->iterations : fractol->saturation;
	lightness = (fractol->damp_lightness) ?
		(float)depth/(float)fractol->iterations : fractol->lightness;
	rgb = hsl_to_rgb(hue, saturation, lightness, fractol->negative);
	//color = ((int)rgb.r << 16) + ((int)rgb.g << 8) + rgb.b;
	return ((int)(((int)rgb.r << 16) + ((int)rgb.g << 8) + rgb.b) & 0x00ffffff);
}
