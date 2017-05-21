/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 16:59:49 by tdefresn          #+#    #+#             */
/*   Updated: 2017/05/21 13:36:31 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	draw_ui(t_context *ctx, int iterations)
{
	void			*win;
	void			*sess;
	t_image			*canvas;
	t_fractol_st	*fractol;
	char			str[32];

	fractol = (t_fractol_st *)ctx->datas;
	win = ctx->win;
	sess = ctx->sess;
	canvas = ctx->canvas;
	ft_sprintf(str, "Number of iterations: %i", iterations);
	mlx_string_put(sess, win, 10, canvas->height - 26, WHITE, str);
	ft_snprintf(str, 32, "Color scheme: %s", fractol->colorset_name);
	mlx_string_put(sess, win, 10, canvas->height - 52, WHITE, str);
	mlx_string_put(sess, win, canvas->width - 190, canvas->height - 26,
			WHITE, "Press [?] for help");
	mlx_string_put(sess, win, canvas->width * 0.5f - 20, 4,
			WHITE, fractol->fractal->name);
}

static void	draw_point(t_context *ctx, t_vec2ui32 *pos, int color,
									int (color_fn)(int, t_fractol_st *))
{
	if (pos->x >= ctx->canvas->width || pos->y >= ctx->canvas->height)
		return ;
	color = color_fn(color, ((t_fractol_st *)ctx->datas));
	set_image_pixel(ctx, ctx->canvas, color, pos);
}

static int	fract(t_context *ctx, t_vec2d *c, int max_depth,
									int (fn)(t_vec2d *, t_vec2d *, int, int))
{
	t_vec2d cc;

	cc.x = c->x;
	cc.y = c->y / ctx->canvas->aspect;
	return (fn(&ctx->mouse_pos, &cc, 0, max_depth));
}

static void	draw_view(t_context *ctx, t_vec2d *min, t_vec2d *max, t_vec2d *step)
{
	int			(*fn)(t_vec2d *, t_vec2d *, int, int);
	int			(*color_fn)(int, t_fractol_st *);
	int			max_depth;
	t_vec2ui32	coord;
	t_vec2d		c;

	fn = ((t_fractol_st *)ctx->datas)->fractal->fn;
	color_fn = ((t_fractol_st *)ctx->datas)->color_fn;
	max_depth = ((t_fractol_st *)ctx->datas)->iterations;
	c.x = min->x;
	coord.x = 0;
	while (c.x < max->x)
	{
		coord.y = 0;
		c.y = min->y;
		while (c.y < max->y)
		{
			draw_point(ctx, &coord, fract(ctx, &c, max_depth, fn), color_fn);
			c.y += step->y;
			coord.y++;
		}
		c.x += step->x;
		coord.x++;
	}
}

void		draw(t_context *ctx)
{
	t_viewport *viewport;

	viewport = &ctx->viewport;
#ifdef FRACTOL_OPENCL
	t_vec2ui32 pos;
	int color;
	pos.x = 0;
	pos.y = 0;
	cl_draw(&ctx->gpgpu, ctx->canvas->width, 1, ((t_fractol_st *)ctx->datas)->iterations);
	while(pos.y < ctx->canvas->height)
	{
		pos.x = 0;
		while (pos.x < ctx->canvas->width)
		{
			color = ctx->gpgpu.buffer[pos.y * ctx->canvas->width + pos.x];
			set_image_pixel(ctx, ctx->canvas, color, &pos);
			pos.x++;
		}
		pos.y++;
	}
	if (false)
		draw_view(ctx, &viewport->min, &viewport->max, &viewport->step);

#else
	draw_view(ctx, &viewport->min, &viewport->max, &viewport->step);
#endif
	mlx_put_image_to_window(ctx->sess, ctx->win, ctx->canvas->img, 0, 0);
	if (ctx->settings.draw_gui)
	{
		draw_ui(ctx, ((t_fractol_st *)ctx->datas)->iterations);
		draw_gui(ctx);
	}
}
