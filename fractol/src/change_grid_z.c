/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_grid_z.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 12:42:29 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/03 18:34:55 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	change_grid_z(t_grid *grid, float f)
{
	int		i;
	int		j;
	int		l;

	i = 0;
	l = grid->width * grid->height * 2;
	while (i < l)
	{
		j = 0;
		while (j < 3)
			grid->triangles[i][j++].coord.z *= f;
		i++;
	}
}
