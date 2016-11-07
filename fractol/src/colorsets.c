/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorsets.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 13:08:11 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/07 20:59:06 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		colorset_deepblue(int depth, t_fractol_st *fractol)
{
	unsigned char		r;
	unsigned char		g;
	unsigned int		b;

	r = 0;
	g = 0;
	b = fractol->iterations - depth;
	b *= 3;
	if (fractol->negative)
	{
		r = 255 - r;
		g = 255 - g;
		b = 255 - b;
	}
	b = (b > 255) ? 255 : b;
	return (((int)r << 16) + ((int)g << 8) + (unsigned char)b);
}

int		colorset_burning(int depth, t_fractol_st *fractol)
{
	unsigned int		r;
	unsigned int		g;
	unsigned int		b;
	unsigned int		c;

	//c = 3 * log(depth) / log(fractol->iterations - 1.0);
	c = 3 * log(depth) / log(fractol->iterations - 1.0);
	if (c < 1)
	{
		r = 255 * c;
		g = 0;
		b = 0;
	}
	else if (c < 2)
	{
		r = 255;
		g = 255 * (c - 1);
		b = 0;
	}
	else
	{
		r = 255;
		g = 255;
		b = 255 * (c - 2);
	}
	if (fractol->negative)
	{
		r = 255 - r;
		g = 255 - g;
		b = 255 - b;
	}
	return (((int)r << 16) + ((int)g << 8) + b);
}

int		colorset_smooth(int depth, t_fractol_st *fractol)
{
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;

	r = depth;
	g = r + r;
	b = g + g;
	if (fractol->negative)
	{
		r = 255 - r;
		g = 255 - g;
		b = 255 - b;
	}
	return (((int)r << 16) + ((int)g << 8) + b);
}

int		colorset_pastel(int depth, t_fractol_st *fractol)
{
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;

	r = 0;
	g = fractol->iterations - depth;
	b = fractol->iterations - depth;
	if (fractol->negative)
	{
		r = 255 - r;
		g = 255 - g;
		b = 255 - b;
	}
	return (((int)r << 16) + ((int)g << 8) + b);
}
