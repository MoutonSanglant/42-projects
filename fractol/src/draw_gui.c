/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_gui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 00:28:43 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/08 13:51:10 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	tooltip_str(t_mlx_st *mlx, char *str, int line, int padding)
{
	mlx_string_put(mlx->sess, mlx->win,
			padding, line * GUI_LINE_HEIGHT, GUI_COLOR, str);
}

static void	draw_help_tooltip(t_mlx_st *mlx)
{
	int		line;

	line = 0;
	tooltip_str(mlx, "Help", line++, 5);
	tooltip_str(mlx, "[.] Hide GUI", line++, 20);
	tooltip_str(mlx, "[+] Zoom in", line++, 20);
	tooltip_str(mlx, "[-] Zoom out", line++, 20);
	tooltip_str(mlx, "[Arrows] Pan view", line++, 20);
	tooltip_str(mlx, "HSL", line++, 5);
	tooltip_str(mlx, "(CTRL)(SHIFT)[H]ue ", line++, 20);
	tooltip_str(mlx, "(CTRL)(SHIFT)[S]aturation ", line++, 20);
	tooltip_str(mlx, "(CTRL)(SHIFT)[L]ightness ", line++, 20);
	tooltip_str(mlx, "RGB", line++, 5);
	tooltip_str(mlx, "(CTRL)[R]ed ", line++, 20);
	tooltip_str(mlx, "(CTRL)[G]reen ", line++, 20);
	tooltip_str(mlx, "(CTRL)[B]lue ", line++, 20);
	tooltip_str(mlx, "Extra", line++, 5);
	tooltip_str(mlx, "[N]egative ", line++, 20);
	tooltip_str(mlx, "(SHIFT)[TAB] Change color scheme", line++, 20);
	tooltip_str(mlx, "[ESC] Exit", line++, 20);
}

#ifdef DEBUG

void		draw_gui(t_mlx_st *mlx)
{
	(void)draw_help_tooltip;
	draw_debug_gui(mlx);
}

#else

void		draw_gui(t_mlx_st *mlx)
{
	if (!mlx->settings.tooltip)
		return ;
	draw_help_tooltip(mlx);
}

#endif
