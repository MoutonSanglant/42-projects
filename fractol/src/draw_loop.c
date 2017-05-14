/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 14:16:46 by tdefresn          #+#    #+#             */
/*   Updated: 2017/05/14 18:34:10 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#ifdef BONUS

static int	get_fps(t_context *ctx)
{
	static int		frames = 0;
	static double	fps = 0;
	struct timeval	tval_now;

	frames++;
	gettimeofday(&tval_now, NULL);
	timersub(&tval_now, &ctx->last_tval, &tval_now);
	if (tval_now.tv_sec * 1000000 + tval_now.tv_usec > 1000000)
	{
		fps = (double)frames / (double)tval_now.tv_sec
			+ (double)tval_now.tv_usec / 1000000;
		fps = (fps > 60) ? 60 : fps;
		gettimeofday(&ctx->last_tval, NULL);
		ctx->need_update = 1;
		frames = 0;
	}
	return ((int)fps);
}

int			draw_loop(void *p)
{
	t_context	*ctx;
	char		str[7];
	int			fps;

	ctx = (t_context *)p;
	fps = get_fps(ctx);
	if (ctx->need_update)
	{
		ctx->draw_fn(ctx);
		if (ctx->settings.draw_gui)
		{
			ft_snprintf(str, 7, "%2.2i FPS", fps);
			mlx_string_put(ctx->sess, ctx->win,
					ctx->canvas->width - 80, 4, WHITE, str);
		}
		ctx->need_update = 0;
	}
	return (0);
}

#else

int			draw_loop(void *p)
{
	t_context		*ctx;

	ctx = (t_context *)p;
	if (ctx->need_update)
	{
		ctx->draw_fn(ctx);
		ctx->need_update = 0;
	}
	return (0);
}

#endif
