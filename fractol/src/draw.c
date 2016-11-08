/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 16:59:49 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/08 03:16:02 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	draw_ui(t_mlx_st *mlx, int iterations)
{
	void			*win;
	void			*sess;
	t_image			*canvas;
	t_fractol_st	*fractol;
	char			str[32];

	fractol = (t_fractol_st *)mlx->datas;
	win = mlx->win;
	sess = mlx->sess;
	canvas = mlx->canvas;
	mlx_put_image_to_window(sess, win, canvas->img, 0, 0);
	ft_sprintf(str, "Number of iterations: %i", iterations);
	mlx_string_put(sess, win, 10, canvas->height - 26, WHITE, str);
	ft_snprintf(str, 32, "Color scheme: %s", fractol->colorset_name);
	mlx_string_put(sess, win, 10, canvas->height - 52, WHITE, str);
	mlx_string_put(sess, win, canvas->width - 190, canvas->height - 26,
			WHITE, "Press [?] for help");
	mlx_string_put(sess, win, canvas->width * 0.5f - 20, 4,
			WHITE, fractol->fractal->name);
}

static void	draw_point(t_mlx_st *mlx, t_vec2ui32 *pos, int color,
									int (color_fn)(int, t_fractol_st *))
{
	if (pos->x >= mlx->canvas->width || pos->y >= mlx->canvas->height)
		return ;
	color = color_fn(color, ((t_fractol_st *)mlx->datas));
	set_image_pixel(mlx, mlx->canvas, color, pos);
}

static int	fract(t_mlx_st *mlx, t_vec2d *c, int max_depth,
									int (fn)(t_vec2d *, t_vec2d *, int, int))
{
	t_vec2d cc;

	cc.x = c->x;
	cc.y = c->y / mlx->canvas->aspect;
	return (fn(&mlx->mouse_pos, &cc, 0, max_depth));
}

static void	draw_view(t_mlx_st *mlx, t_vec2d *min, t_vec2d *max, t_vec2d *step)
{
	int			(*fn)(t_vec2d *, t_vec2d *, int, int);
	int			(*color_fn)(int, t_fractol_st *);
	int			max_depth;
	t_vec2ui32	coord;
	t_vec2d		c;

	fn = ((t_fractol_st *)mlx->datas)->fractal->fn;
	color_fn = ((t_fractol_st *)mlx->datas)->color_fn;
	max_depth = ((t_fractol_st *)mlx->datas)->iterations;
	c.x = min->x;
	coord.x = 0;
	while (c.x < max->x)
	{
		coord.y = 0;
		c.y = min->y;
		while (c.y < max->y)
		{
			draw_point(mlx, &coord, fract(mlx, &c, max_depth, fn), color_fn);
			c.y += step->y;
			coord.y++;
		}
		c.x += step->x;
		coord.x++;
	}
}

void		draw(t_mlx_st *mlx)
{
	t_viewport *viewport;

	viewport = &mlx->viewport;
	draw_view(mlx, &viewport->min, &viewport->max, &viewport->step);
	draw_ui(mlx, ((t_fractol_st *)mlx->datas)->iterations);
	draw_gui(mlx);
}
