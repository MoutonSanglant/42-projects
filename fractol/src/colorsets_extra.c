/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorsets_extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 16:13:33 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/07 20:12:04 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		colorset_psycho(int depth, t_fractol_st *fractol)
{
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;

	r = depth * 13;
	g = depth * 157;
	b = depth * 79;
	if (fractol->negative)
	{
		r = 255 - r;
		g = 255 - g;
		b = 255 - b;
	}
	return (((int)r << 16) + ((int)g << 8) + b);
}

int		colorset_square(int depth, t_fractol_st *fractol)
{
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;

	r = depth;
	g = r * r;
	b = g * g;
	if (fractol->negative)
	{
		r = 255 - r;
		g = 255 - g;
		b = 255 - b;
	}
	return (((int)r << 16) + ((int)g << 8) + b);
}

int		colorset_prismatic(int depth, t_fractol_st *fractol)
{
	t_color		rgb;

	rgb = hsl_to_rgb((float)depth / (float)fractol->iterations,
			1.f, (float)depth / (float)fractol->iterations, fractol->negative);
	if (fractol->negative)
	{
		rgb.r = 255 - rgb.r;
		rgb.g = 255 - rgb.g;
		rgb.b = 255 - rgb.b;
	}
	return ((int)(((int)rgb.r << 16) + ((int)rgb.g << 8) + rgb.b) & 0x00ffffff);
}

int		colorset_parametric(int depth, t_fractol_st *fractol)
{
	t_color		rgb;

	rgb.r = depth * fractol->color.r;
	rgb.g = depth * fractol->color.g;
	rgb.g = (rgb.g < 255) ? rgb.g : 255;
	rgb.b = depth * fractol->color.b;
	rgb.b = (rgb.b < 255) ? rgb.b : 255;
	if (fractol->negative)
	{
		rgb.r = 255 - rgb.r;
		rgb.g = 255 - rgb.g;
		rgb.b = 255 - rgb.b;
	}
	return (((int)rgb.r << 16) + ((int)rgb.g << 8) + rgb.b);
}

int		colorset_parametric_hsl(int depth, t_fractol_st *fractol)
{
	t_color		rgb;
	float		hue;
	float		saturation;
	float		lightness;

	hue = (fractol->damp_hue) ?
		(float)depth / (float)fractol->iterations : fractol->hue;
	saturation = (fractol->damp_saturation) ?
		(float)depth / (float)fractol->iterations : fractol->saturation;
	lightness = (fractol->damp_lightness) ?
		(float)depth / (float)fractol->iterations : fractol->lightness;
	rgb = hsl_to_rgb(hue, saturation, lightness, fractol->negative);
	return ((int)(((int)rgb.r << 16) + ((int)rgb.g << 8) + rgb.b) & 0x00ffffff);
}
