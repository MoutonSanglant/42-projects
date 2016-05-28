/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorsets.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 13:08:11 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/28 17:16:38 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		colorset_deepblue(int depth, t_fractol_st *fractol_st)
{
	(void)fractol_st;
	return (BLACK + depth * 10);
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

int		colorset_smooth(int depth, t_fractol_st *fractol_st)
{
	int		color;
	unsigned char		r;
	unsigned char		g;
	unsigned char		b;

	(void)fractol_st;
	r =  depth;
	g =  r + r;
	b =  g + g;
	color = ((int)r << 16) + ((int)g << 8) + b;
	return (color);
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
