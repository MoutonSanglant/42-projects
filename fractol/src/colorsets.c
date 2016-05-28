/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorsets.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 13:08:11 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/28 04:29:11 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		colorset_deepblue(int depth, t_fractol_st *fractol_st)
{
	(void)fractol_st;
	return (BLACK + depth * 10);
}

int		colorset_greyradiosity(int depth, t_fractol_st *fractol_st)
{
	int		color;
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;

	(void)fractol_st;
	r =  (depth > 255) ? 255 : depth;
	g =  (depth > 255) ? 255 : depth;
	b =  (depth > 255) ? 255 : depth;
	color = ((int)r << 16) + ((int)g << 8) + b;
	return (color);
}

int		colorset_burning(int depth, t_fractol_st *fractol_st)
{
	int		color;
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;

	(void)fractol_st;
	r =  (depth * 7 > 255) ? 255 : depth * 7;
	g =  (depth > 255) ? 255 : depth;
	b =  (depth > 255) ? 255 : depth;
	color = ((int)r << 16) + ((int)g << 8) + b;
	return (color);
}

int		colorset_parametric(int depth, t_fractol_st *fractol_st)
{
	int		color;
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;

	r =  (depth * fractol_st->color.r > 255) ? 255 : depth * fractol_st->color.r;
	g =  (depth * fractol_st->color.g > 255) ? 255 : depth * fractol_st->color.g;
	b =  (depth * fractol_st->color.b > 255) ? 255 : depth * fractol_st->color.b;
	color = ((int)r << 16) + ((int)g << 8) + b;
	return (color);
}
