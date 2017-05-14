/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_gui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 00:28:43 by tdefresn          #+#    #+#             */
/*   Updated: 2017/05/14 18:34:47 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	tooltip_str(t_context *ctx, char *str, int line, int padding)
{
	mlx_string_put(ctx->sess, ctx->win,
			padding, line * GUI_LINE_HEIGHT, GUI_COLOR, str);
}

static void	draw_help_tooltip(t_context *ctx)
{
	int		line;

	line = 0;
	tooltip_str(ctx, "Help", line++, 5);
	tooltip_str(ctx, "[.] Hide GUI", line++, 20);
	tooltip_str(ctx, "[+] Zoom in", line++, 20);
	tooltip_str(ctx, "[-] Zoom out", line++, 20);
	tooltip_str(ctx, "[Arrows] Pan view", line++, 20);
	tooltip_str(ctx, "HSL", line++, 5);
	tooltip_str(ctx, "(CTRL)(SHIFT)[H]ue ", line++, 20);
	tooltip_str(ctx, "(CTRL)(SHIFT)[S]aturation ", line++, 20);
	tooltip_str(ctx, "(CTRL)(SHIFT)[L]ightness ", line++, 20);
	tooltip_str(ctx, "RGB", line++, 5);
	tooltip_str(ctx, "(CTRL)[R]ed ", line++, 20);
	tooltip_str(ctx, "(CTRL)[G]reen ", line++, 20);
	tooltip_str(ctx, "(CTRL)[B]lue ", line++, 20);
	tooltip_str(ctx, "Extra", line++, 5);
	tooltip_str(ctx, "[N]egative ", line++, 20);
	tooltip_str(ctx, "(SHIFT)[TAB] Change color scheme", line++, 20);
	tooltip_str(ctx, "[ESC] Exit", line++, 20);
}

#ifdef DEBUG

void		draw_gui(t_context *ctx)
{
	(void)draw_help_tooltip;
	draw_debug_gui(ctx);
}

#else

void		draw_gui(t_context *ctx)
{
	if (!ctx->settings.tooltip)
		return ;
	draw_help_tooltip(ctx);
}

#endif
