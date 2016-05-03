/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_gui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 00:28:43 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/04 01:18:17 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	draw_help_tooltip(void *s, void *w, int line)
{
	mlx_string_put(s, w, 20, line++ * GUI_LINE_HEIGHT, WHITE, "[+] Zoom in");
	mlx_string_put(s, w, 20, line++ * GUI_LINE_HEIGHT, WHITE, "[-] Zoom out");
	mlx_string_put(s, w, 20, line++ * GUI_LINE_HEIGHT, WHITE, "[Arrows] Pan");
	mlx_string_put(s, w, 20, line++ * GUI_LINE_HEIGHT, WHITE,
					"[W/A/S/D/Q/E] Rotate");
	mlx_string_put(s, w, 20, line++ * GUI_LINE_HEIGHT, WHITE,
					"[PAGE UP/DOWN] Rise/Lower vertices");
	mlx_string_put(s, w, 20, line++ * GUI_LINE_HEIGHT, WHITE, "[O]rthographic");
	mlx_string_put(s, w, 20, line++ * GUI_LINE_HEIGHT, WHITE, "[P]erspective");
	mlx_string_put(s, w, 20, line++ * GUI_LINE_HEIGHT, WHITE,
					"[B]ackface culling");
	mlx_string_put(s, w, 20, line++ * GUI_LINE_HEIGHT, WHITE,
					"[I]nvert colors");
	mlx_string_put(s, w, 20, line++ * GUI_LINE_HEIGHT, WHITE, "[Z]-Buffer");
	mlx_string_put(s, w, 20, line++ * GUI_LINE_HEIGHT, WHITE, "[F]ill faces");
	mlx_string_put(s, w, 20, line++ * GUI_LINE_HEIGHT, WHITE,
					"[*] Line weight");
	mlx_string_put(s, w, 20, line++ * GUI_LINE_HEIGHT, WHITE,
					"[0-4] Color schemes");
	mlx_string_put(s, w, 20, line++ * GUI_LINE_HEIGHT, WHITE, "[ESC] Exit");
}

# ifdef DEBUG

void		draw_gui(t_mlx_st *mlx)
{
	(void)draw_help_tooltip;
	draw_debug_gui(mlx);
}

# else

void		draw_gui(t_mlx_st *mlx)
{
	void	*s;
	void	*w;
	int		line;

	if (!mlx->options.tooltip)
		return ;
	line = 1;
	s = mlx->sess;
	w = mlx->win;
	if (mlx->canvas->filename)
	{
		mlx_string_put(s, w, 5, line * GUI_LINE_HEIGHT, WHITE, "Source file: ");
		mlx_string_put(s, w, 155, line++ * GUI_LINE_HEIGHT, WHITE,
														mlx->canvas->filename);
	}
	mlx_string_put(s, w, 5, line++ * GUI_LINE_HEIGHT, 0x00ffffff, "[H]elp");
	draw_help_tooltip(s, w, line);
}

# endif

