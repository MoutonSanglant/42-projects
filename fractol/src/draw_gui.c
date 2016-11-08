/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_gui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 00:28:43 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/07 22:38:34 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	draw_help_tooltip(void *s, void *w, int line)
{
	mlx_string_put(s, w, 20, line++ * GUI_LINE_HEIGHT, WHITE, "[+] Zoom in");
	mlx_string_put(s, w, 20, line++ * GUI_LINE_HEIGHT, WHITE, "[-] Zoom out");
	mlx_string_put(s, w, 20, line++ * GUI_LINE_HEIGHT, WHITE, "[Arrows] Pan");
	mlx_string_put(s, w, 5, line++ * GUI_LINE_HEIGHT, WHITE, "HSL:");
	mlx_string_put(s, w, 20, line++ * GUI_LINE_HEIGHT, WHITE, "[H]ue");
	mlx_string_put(s, w, 20, line++ * GUI_LINE_HEIGHT, WHITE, "[S]aturation");
	mlx_string_put(s, w, 20, line++ * GUI_LINE_HEIGHT, WHITE, "[L]ightness");
	mlx_string_put(s, w, 5, line++ * GUI_LINE_HEIGHT, WHITE, "RGB:");
	mlx_string_put(s, w, 20, line++ * GUI_LINE_HEIGHT, WHITE, "[R]ed");
	mlx_string_put(s, w, 20, line++ * GUI_LINE_HEIGHT, WHITE, "[G]reen");
	mlx_string_put(s, w, 20, line++ * GUI_LINE_HEIGHT, WHITE, "[B]lue");
	mlx_string_put(s, w, 20, line++ * GUI_LINE_HEIGHT, WHITE, "[N]egative");
	mlx_string_put(s, w, 20, line++ * GUI_LINE_HEIGHT, WHITE,
			"[SHIFT] Increase value");
	mlx_string_put(s, w, 20, line++ * GUI_LINE_HEIGHT, WHITE,
			"[CTRL] Decrease value");
	mlx_string_put(s, w, 20, line++ * GUI_LINE_HEIGHT, WHITE,
			"[TAB] Change color");
	mlx_string_put(s, w, 20, line++ * GUI_LINE_HEIGHT, WHITE, "[ESC] Exit");
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
	void	*s;
	void	*w;
	int		line;

	if (!mlx->settings.tooltip)
		return ;
	line = 1;
	s = mlx->sess;
	w = mlx->win;
	draw_help_tooltip(s, w, line);
}

#endif
