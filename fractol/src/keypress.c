/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 14:14:47 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/04 00:02:59 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		keypress(int key, void *p)
{
	t_mlx_st	*mlx;

	mlx = (t_mlx_st *)p;
	if (key == KEY_ESCAPE)
	{
		destroy_mlx_sess(mlx);
		exit(0);
	}
	return (0);
}
