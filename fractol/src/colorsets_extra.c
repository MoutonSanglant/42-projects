/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorsets_extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 16:13:33 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/28 17:20:50 by tdefresn         ###   ########.fr       */
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
	int		color;
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;

	(void)fractol_st;
	if (depth < 30)
	{
		r = depth * 7;
		g = depth;
		b = depth;
	}
	else if (depth < 60)
	{
		r = depth;
		g = depth;
		b = depth * 7;
	}
	else if (depth < 90)
	{
		r = depth;
		g = depth * 7;
		b = depth;
	}
	else if (depth < 120)
	{
		r = depth * 7;
		g = depth;
		b = depth * 7;
	}
	else if (depth < 150)
	{
		r = depth * 7;
		g = depth * 7;
		b = depth;
	}
	else if (depth < 180)
	{
		r = depth;
		g = depth * 7;
		b = depth * 7;
	}
	else if (depth < 210)
	{
		r = depth * 7;
		g = depth * 7;
		b = depth * 7;
	}
	else
	{
		r = depth;
		g = depth;
		b = depth;
	}
	color = ((int)r << 16) + ((int)g << 8) + b;
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
