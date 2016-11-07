/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorscheme.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 17:32:45 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/07 21:00:00 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	loop_colorschemes(t_fractol_st *fractol, int modifier)
{
	static int	scheme = 0;

	if (modifier)
		scheme--;
	else
		scheme++;
	if (scheme > 8)
		scheme = 0;
	else if (scheme < 0)
		scheme = 8;
	set_colorscheme(fractol, scheme);
}

void	set_colorscheme(t_fractol_st *fractol, int scheme)
{
	static const t_colorset	set_list[9] = {
		{ "Parametric HSL", &colorset_parametric_hsl },
		{ "Burning", &colorset_burning },
		{ "Pastel", &colorset_pastel },
		{ "Deep blue", &colorset_deepblue },
		{ "Smooth", &colorset_smooth },
		{ "Prismatic", &colorset_prismatic },
		{ "Parametric RGB", &colorset_parametric },
		{ "Square", &colorset_square },
		{ "Psychedelic", &colorset_psycho }
	};

	fractol->color_fn = set_list[scheme].fn;
	fractol->colorset_name = set_list[scheme].name;
}
