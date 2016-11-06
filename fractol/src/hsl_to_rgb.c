/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hsl_to_rgb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/29 16:54:09 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/06 23:57:13 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	set_sextant_odd(int sextant, t_color *rgb, float mid, float v, float m)
{
	if (sextant == 1)
	{
		rgb->r = mid;
		rgb->g = v;
		rgb->b = m;
	}
	else if (sextant == 3)
	{
		rgb->r = m;
		rgb->g = mid;
		rgb->b = v;
	}
	else if (sextant == 5)
	{
		rgb->r = v;
		rgb->g = m;
		rgb->b = mid;
	}
}

static void	set_sextant_even(int sextant, t_color *rgb, float mid, float v, float m)
{
	if (sextant == 0)
	{
		rgb->r = v;
		rgb->g = mid;
		rgb->b = m;
	}
	else if (sextant == 2)
	{
		rgb->r = m;
		rgb->g = v;
		rgb->b = mid;
	}
	else if (sextant == 4)
	{
		rgb->r = mid;
		rgb->g = m;
		rgb->b = v;
	}
}

static void	convert(t_color *rgb, float h, float l, float v)
{
	int		sextant;
	float	fract;
	float	vsf;
	float	sv;
	float	m;

	m = l + l - v;
	sv = (v - m ) / v;
	h *= 6.0;
	sextant = (int)h;
	fract = h - sextant;
	vsf = v * sv * fract;
	if (sextant % 2)
		set_sextant_odd(sextant, rgb, v - vsf, v, m);
	else
		set_sextant_even(sextant, rgb, m + vsf, v, m);
}

t_color		hsl_to_rgb(float h, float sl, float l, int invert)
{
	t_color		rgb;
	float		v;

	rgb.r = l;
	rgb.g = l;
	rgb.b = l;
	v = (l <= 0.5) ? (l * (1.0 + sl)) : (l + sl - l * sl);
	if (v < 0)
		v+= 360.f;

	convert(&rgb, h, l, v);
	rgb.r = rgb.r * 255.0f;
	rgb.g = rgb.g * 255.0f;
	rgb.b = rgb.b * 255.0f;
	if (invert)
	{
		rgb.r = 255 - rgb.r;
		rgb.g = 255 - rgb.g;
		rgb.b = 255 - rgb.b;
	}
	return (rgb);
}
