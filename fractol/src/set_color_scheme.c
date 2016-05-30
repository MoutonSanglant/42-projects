/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color_scheme.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 22:20:40 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/30 15:49:49 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	set_color_scheme(t_fractol_st *fractol, int scheme)
{
	if (scheme == 0)
	{
		fractol->color_fn = &colorset_parametric_hsl;
		fractol->colorset_name = "Parametric HSL";
	}
	else if (scheme == 1)
	{
		fractol->color_fn = &colorset_burning;
		fractol->colorset_name = "Burning";
	}
	else if (scheme == 2)
	{
		fractol->color_fn = &colorset_deepblue;
		fractol->colorset_name = "Deep blue";
	}
	else if (scheme == 3)
	{
		fractol->color_fn = &colorset_smooth;
		fractol->colorset_name = "Smooth";
	}
	else if (scheme == 4)
	{
		fractol->color_fn = &colorset_prismatic;
		fractol->colorset_name = "Prismatic";
	}
	else if (scheme == 5)
	{
		fractol->color_fn = &colorset_parametric;
		fractol->colorset_name = "Parametric RGB";
	}
	else if (scheme == 6)
	{
		fractol->color_fn = &colorset_square;
		fractol->colorset_name = "Square";
	}
	else if (scheme == 7)
	{
		fractol->color_fn = &colorset_psycho;
		fractol->colorset_name = "Psychedelic";
	}
}
