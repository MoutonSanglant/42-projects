/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 17:48:19 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/06 17:52:03 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** f[{a_, b_}] := {a*a - b*b + c1, 2*a*b + c2}]
*/
int		julia(double c1, double c2, int max_depth)
{
	double		modulus;
	double		escape_radius = 20.f;
	double		a;
	double		b;
	double		a_;
	double		b_;
	int			depth;

	a = 0;
	b = 0;
	depth = 0;
	modulus = 0;
	while (modulus < escape_radius && depth < max_depth)
	{
		a_ = a;
		b_ = b;
		a = a_ * a_ - b_ * b_ + c1;
		b = 2 * a_ * b_ + c2;
		modulus = fabs(a) + fabs(b);
		depth++;
	}
	//return ((depth < 20) ? 0 : 100);
	return (depth);
}
