/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorsets_extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 16:13:33 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/29 19:05:28 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		colorset_psycho(int depth, t_fractol_st *fractol_st)
{
	int		color;
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;

	(void)fractol_st;
	r =  depth * 13;
	g =  depth * 157;
	b =  depth * 79;
	color = ((int)r << 16) + ((int)g << 8) + b;
	return (color);
}

int		colorset_square(int depth, t_fractol_st *fractol_st)
{
	int		color;
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;

	(void)fractol_st;
	r =  depth;
	g =  r * r;
	b =  g * g;
	color = ((int)r << 16) + ((int)g << 8) + b;
	return (color);
}

int		colorset_prismatic(int depth, t_fractol_st *fractol_st)
{
	int			color;
	t_color		rgb;

	(void)fractol_st;
	rgb = hsl_to_rgb((float)depth/(float)ITERATIONS_LIMIT,
			1.f, (float)depth/(float)ITERATIONS_LIMIT);
	color = ((int)rgb.r << 16) + ((int)rgb.g << 8) + rgb.b;
	color &= 0x00ffffff;
	return (color);
}


int		colorset_parametric(int depth, t_fractol_st *fractol_st)
{
	int			color;
	t_color		rgb;

	rgb.r =  depth * fractol_st->color.r;
	rgb.g =  (depth * fractol_st->color.g > 255) ? 255 : depth * fractol_st->color.g;
	rgb.b =  (depth * fractol_st->color.b > 255) ? 255 : depth * fractol_st->color.b;
	color = ((int)rgb.r << 16) + ((int)rgb.g << 8) + rgb.b;
	return (color);
}

int		colorset_parametric_hsl(int depth, t_fractol_st *fractol_st)
{
	int			color;
	t_color		rgb;
	double		hue;
	double		saturation;
	double		lightness;

	hue = fractol_st->hue;
	saturation = fractol_st->saturation;
	lightness = fractol_st->lightness;
	if (fractol_st->damp_hue)
		hue = (float)depth/(float)ITERATIONS_LIMIT;
	if (fractol_st->damp_saturation)
		saturation = (float)depth/(float)ITERATIONS_LIMIT;
	if (fractol_st->damp_lightness)
		lightness = (float)depth/(float)ITERATIONS_LIMIT;
	rgb = hsl_to_rgb(hue, saturation, lightness);
	color = ((int)rgb.r << 16) + ((int)rgb.g << 8) + rgb.b;
	return (color);
}
