/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorsets_extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 16:13:33 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/29 18:21:36 by tdefresn         ###   ########.fr       */
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

	(void)depth;
	(void)fractol_st;
	//rgb = hsl_to_rgb(.5f, 255.f/(float)depth, .5f);
	rgb = hsl_to_rgb((float)depth/(float)ITERATIONS_LIMIT, 1.f, .7f);
	color = ((int)rgb.r << 16) + ((int)rgb.g << 8) + rgb.b;
	//color = ((int)rgb.b << 16) + ((int)rgb.g << 8) + rgb.r;
	color &= 0x00ffffff;
	//color |= 0xff000000;
	return (color);
}


int		colorset_parametric(int depth, t_fractol_st *fractol_st)
{
	int		color;
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;

	r =  depth * fractol_st->color.r;
	//r =  (depth * fractol_st->color.r > 255) ? 255 : depth * fractol_st->color.r;
	g =  (depth * fractol_st->color.g > 255) ? 255 : depth * fractol_st->color.g;
	b =  (depth * fractol_st->color.b > 255) ? 255 : depth * fractol_st->color.b;
	color = ((int)r << 16) + ((int)g << 8) + b;
	return (color);
}
