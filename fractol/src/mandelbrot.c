/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 17:47:22 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/06 19:01:52 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** f[{a_, b_}] := {a*a - b*b + c1, 2*a*b + c2}]
*/
int		mandelbrot(double c1, double c2, int max_depth)
{
	double		a;
	double		b;
	double		a_;
	double		b_;
	int			depth;

	a = c1;
	b = c2;
	depth = 1;
	while (depth < max_depth && fabs(a) + fabs(b) < ESCAPE_RADIUS)
	{
		a_ = a;
		b_ = b;
		a = a_ * a_ - b_ * b_ + c1;
		a_ += a_;
		b = a_ * b_ + c2;
		depth++;
	}
	return (depth);
}

/*
** //colorless:
** return ((depth < 20) ? 0 : 100);
*/
