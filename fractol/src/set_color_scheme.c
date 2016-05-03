/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color_scheme.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 22:20:40 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/03 18:34:55 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	set_color_scheme(t_mlx_sess *sess, int lines_color,
							int faces_color, int bg_color)
{
	sess->options.lines_color = lines_color;
	sess->options.faces_color = faces_color;
	sess->options.bg_color = bg_color;
}
