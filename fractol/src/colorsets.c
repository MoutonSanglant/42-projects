/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorsets.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 13:08:11 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/08 14:38:24 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		colorset_deepblue(int depth, t_fractol_st *fractol)
{
	t_color		rgb;

	if (depth > fractol->iterations)
		return (0);
	ft_bzero(&rgb, sizeof(t_color));
	rgb.g = (float)depth / (float)fractol->iterations * 205.f;
	rgb.b = (float)depth / (float)fractol->iterations * 255.f;
	if (fractol->negative)
	{
		rgb.r = 255.f - rgb.r;
		rgb.g = 255.f - rgb.g;
		rgb.b = 255.f - rgb.b;
	}
	return ((int)(((int)rgb.r << 16) + ((int)rgb.g << 8) + (int)rgb.b)
			& 0x00ffffff);
}

int		colorset_burning(int depth, t_fractol_st *fractol)
{
	t_color		rgb;
	float		c;

	if (depth > fractol->iterations)
		return (0);
	ft_bzero(&rgb, sizeof(t_color));
	c = 2.f * logf((float)depth) / logf((float)fractol->iterations - 1.f);
	rgb.r = 255.f;
	if (c < 1.f)
		rgb.r = 255.f * c;
	else if (c < 2.f)
		rgb.g = 255.f * (c - 1.f);
	else
	{
		rgb.b = 255.f * (c - 2.f);
	}
	if (fractol->negative)
	{
		rgb.r = 255.f - rgb.r;
		rgb.g = 255.f - rgb.g;
		rgb.b = 255.f - rgb.b;
	}
	return ((int)(((int)rgb.r << 16) + ((int)rgb.g << 8) + (int)rgb.b)
			& 0x00ffffff);
}

int		colorset_smooth(int depth, t_fractol_st *fractol)
{
	t_color		rgb;

	if (depth > fractol->iterations)
		return (0);
	ft_bzero(&rgb, sizeof(t_color));
	rgb.r = (float)depth / (float)fractol->iterations * 255.f;
	rgb.g = rgb.r + rgb.r;
	rgb.b = rgb.g + rgb.g;
	if (fractol->negative)
	{
		rgb.r = 255.f - rgb.r;
		rgb.g = 255.f - rgb.g;
		rgb.b = 255.f - rgb.b;
	}
	return ((int)(((int)rgb.r << 16) + ((int)rgb.g << 8) + (int)rgb.b)
			& 0x00ffffff);
}

int		colorset_pastel(int depth, t_fractol_st *fractol)
{
	t_color		rgb;

	ft_bzero(&rgb, sizeof(t_color));
	rgb.r = 255.f - (float)depth / (float)fractol->iterations * 195.f;
	rgb.g = 255.f - (float)depth / (float)fractol->iterations * 75.f;
	rgb.b = 255.f - (float)depth / (float)fractol->iterations * 145.f;
	if (fractol->negative)
	{
		rgb.r = 255.f - rgb.r;
		rgb.g = 255.f - rgb.g;
		rgb.b = 255.f - rgb.b;
	}
	return ((int)(((int)rgb.r << 16) + ((int)rgb.g << 8) + (int)rgb.b)
			& 0x00ffffff);
}
