/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 14:02:46 by tdefresn          #+#    #+#             */
/*   Updated: 2017/05/14 18:45:03 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** Some reading:
**	http://world.mathigon.org/Fractals
**	http://linas.org/art-gallery/escape/escape.html
*/

static void		get_size(int argc, char **argv, t_vec2 *screen_size)
{
	char	str[100];

	screen_size->x = DEFAULT_WIDTH;
	screen_size->y = DEFAULT_HEIGHT;
	if (argc > 3)
	{
		screen_size->x = ft_atoi(argv[0]);
		screen_size->y = ft_atoi(argv[1]);
		if (screen_size->x < MIN_WIDTH || screen_size->x > MAX_WIDTH)
		{
			ft_snprintf(str, 99, "Width must be a value between %i and %i",
														MIN_WIDTH, MAX_WIDTH);
			error(str);
		}
		if (screen_size->y < MIN_HEIGHT || screen_size->y > MAX_HEIGHT)
		{
			ft_snprintf(str, 99, "Height must be a value between %i and %i",
														MIN_HEIGHT, MAX_HEIGHT);
			error(str);
		}
	}
}

static void		set_fractal(char *name, t_fractal *fractal)
{
	static const t_fractal	fractal_list[9] = {
		{ "julia", "Julia", &julia, 1 },
		{ "mandelbrot", "Mandelbrot", &mandelbrot, 0 },
		{ "burning_ship", "Burning Ship", &burning, 0 },
		{ "glynn", "Glynn", &glynn, 0 },
		{ "shell", "Shell", &shell, 0 },
		{ "multibrot6", "Multibrot (power of 6)", &multibrot6, 0 },
		{ "julia_sun", "Julia wave", &julia_sun, 0 },
		{ "julia_wave", "Julia wave", &julia_wave, 0 },
		{ "mandel_spider", "Mandelbrot spider (variant)", &mandel_spider, 0 }
	};
	int						i;

	i = 0;
	while (i < 9)
	{
		if (ft_strequ(name, fractal_list[i].str))
		{
			*fractal = fractal_list[i];
			return ;
		}
		i++;
	}
	error(USAGE_MSG);
}

int				main(int argc, char **argv)
{
	t_context		context;
	t_fractol_st	fractol;
	t_fractal		fractal;
	t_vec2			win_size;

	if (argc < 2 || argc > 4)
		error(USAGE_MSG);
	if (ft_strequ(argv[1], "--help") || ft_strequ(argv[1], "-h"))
		exit(help());
	get_size(argc, &argv[2], &win_size);
	set_fractal(argv[1], &fractal);
	init_fractol(&fractol);
	init_mlx_sess(&context);
	fractol.fractal = &fractal;
	context.settings.mouse_capture = fractal.interactive;
	context.draw_fn = &draw;
	new_window(&context, win_size);
	new_canvas(&context, win_size);
	context.viewport.pos.x = -0.6f;
	context.viewport.zoom_level = 0.6f;
	zoom_viewport(&context.viewport);
	move_viewport(&context.viewport, context.canvas);
	context.datas = (void *)&fractol;
	start_mlx_sess(&context);
	return (0);
}
