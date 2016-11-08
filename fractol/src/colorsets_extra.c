/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorsets_extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 16:13:33 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/08 03:09:09 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		colorset_psycho(int depth, t_fractol_st *fractol)
{
	t_color		rgb;

	if (depth > fractol->iterations)
		return (0);
	ft_bzero(&rgb, sizeof(t_color));
	rgb.r = depth * 255.f;
	rgb.g = 1 / depth * 255.f;
	rgb.b = depth * depth * 255.f;
	if (fractol->negative)
	{
		rgb.r = 255.f - rgb.r;
		rgb.g = 255.f - rgb.g;
		rgb.b = 255.f - rgb.b;
	}
	return ((int)(((int)rgb.r << 16) + ((int)rgb.g << 8) + (int)rgb.b)
				& 0x00ffffff);
}

int		colorset_square(int depth, t_fractol_st *fractol)
{
	t_color		rgb;

	if (depth > fractol->iterations)
		return (0);
	ft_bzero(&rgb, sizeof(t_color));
	rgb.r = depth * 255.f;
	rgb.g = rgb.r * rgb.r;
	rgb.b = rgb.g * rgb.g;
	if (fractol->negative)
	{
		rgb.r = 255.f - rgb.r;
		rgb.g = 255.f - rgb.g;
		rgb.b = 255.f - rgb.b;
	}
	return ((int)(((int)rgb.r << 16) + ((int)rgb.g << 8) + (int)rgb.b)
				& 0x00ffffff);
}

int		colorset_prismatic(int depth, t_fractol_st *fractol)
{
	t_color		rgb;

	if (depth > fractol->iterations)
		return (0);
	hsl_to_rgb(&rgb, (float)depth / (float)fractol->iterations,
			1.f, (float)depth / (float)fractol->iterations);
	if (fractol->negative)
	{
		rgb.r = 255.f - rgb.r;
		rgb.g = 255.f - rgb.g;
		rgb.b = 255.f - rgb.b;
	}
	return ((int)(((int)rgb.r << 16) + ((int)rgb.g << 8) + (int)rgb.b)
				& 0x00ffffff);
}

int		colorset_parametric(int depth, t_fractol_st *fractol)
{
	t_color		rgb;

	if (depth > fractol->iterations)
		return (0);
	ft_bzero(&rgb, sizeof(t_color));
	rgb.r = fractol->color.r;
	rgb.g = fractol->color.g;
	rgb.b = fractol->color.b;
	rgb.r *= (float)depth / (float)fractol->iterations;
	rgb.g *= (float)depth / (float)fractol->iterations;
	rgb.b *= (float)depth / (float)fractol->iterations;
	if (fractol->negative)
	{
		rgb.r = 255.f - rgb.r;
		rgb.g = 255.f - rgb.g;
		rgb.b = 255.f - rgb.b;
	}
	return ((int)(((int)rgb.r << 16) + ((int)rgb.g << 8) + (int)rgb.b)
				& 0x00ffffff);
}

int		colorset_parametric_hsl(int depth, t_fractol_st *fractol)
{
	t_color		rgb;
	float		hue;
	float		saturation;
	float		lightness;

	if (depth > fractol->iterations)
		return (0);
	hue = (fractol->damp_hue) ?
		(float)depth / (float)fractol->iterations : fractol->hue;
	saturation = (fractol->damp_saturation) ?
		(float)depth / (float)fractol->iterations : fractol->saturation;
	lightness = (fractol->damp_lightness) ?
		(float)depth / (float)fractol->iterations : fractol->lightness;
	hsl_to_rgb(&rgb, hue, saturation, lightness);
	if (fractol->negative)
	{
		rgb.r = 255.f - rgb.r;
		rgb.g = 255.f - rgb.g;
		rgb.b = 255.f - rgb.b;
	}
	return ((int)(((int)rgb.r << 16) + ((int)rgb.g << 8) + (int)rgb.b)
				& 0x00ffffff);
}
