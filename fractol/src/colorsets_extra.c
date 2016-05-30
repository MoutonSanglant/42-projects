/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorsets_extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 16:13:33 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/30 14:16:10 by tdefresn         ###   ########.fr       */
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
	int		color;
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;

	(void)fractol;
	r =  depth;
	g =  r * r;
	b =  g * g;
	color = ((int)r << 16) + ((int)g << 8) + b;
	return (color);
}

int		colorset_prismatic(int depth, t_fractol_st *fractol)
{
	int			color;
	t_color		rgb;

	(void)fractol;
	rgb = hsl_to_rgb((float)depth/(float)MAX_ITERATIONS,
			1.f, (float)depth/(float)MAX_ITERATIONS);
	color = ((int)rgb.r << 16) + ((int)rgb.g << 8) + rgb.b;
	color &= 0x00ffffff;
	return (color);
}


int		colorset_parametric(int depth, t_fractol_st *fractol)
{
	int			color;
	t_color		rgb;

	rgb.r = depth * fractol->color.r;
	rgb.g =
		(depth * fractol->color.g > 255) ? 255 : depth * fractol->color.g;
	rgb.b =
		(depth * fractol->color.b > 255) ? 255 : depth * fractol->color.b;
	color = ((int)rgb.r << 16) + ((int)rgb.g << 8) + rgb.b;
	return (color);
}

int		colorset_parametric_hsl(int depth, t_fractol_st *fractol)
{
	int			color;
	t_color		rgb;
	double		hue;
	double		saturation;
	double		lightness;

	hue = fractol->hue;
	saturation = fractol->saturation;
	lightness = fractol->lightness;
	if (fractol->damp_hue)
		hue += (float)depth/(float)MAX_ITERATIONS;
	if (fractol->damp_saturation)
		saturation += (float)depth/(float)MAX_ITERATIONS;
	if (fractol->damp_lightness)
		lightness += (float)depth/(float)MAX_ITERATIONS;
	rgb = hsl_to_rgb(hue, saturation, lightness);
	color = ((int)rgb.r << 16) + ((int)rgb.g << 8) + rgb.b;
	color &= 0x00ffffff;
	return (color);
}
