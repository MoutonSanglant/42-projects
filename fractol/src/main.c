/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 14:02:46 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/06 22:42:54 by tdefresn         ###   ########.fr       */
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
			ft_snprintf(str, 99, "Width must be a value between %i and %i\n",
														MIN_WIDTH, MAX_WIDTH);
			error(str);
		}
		if (screen_size->y < MIN_HEIGHT || screen_size->y > MAX_HEIGHT)
		{
			ft_snprintf(str, 99, "Height must be a value between %i and %i\n",
														MIN_HEIGHT, MAX_HEIGHT);
			error(str);
		}
	}
}

static void		set_fractal(char *name, t_fractal *fractal)
{
	fractal->interactive = 0;
	if (ft_strequ(name, "mandelbrot"))
	{
		fractal->name = "Mandelbrot";
		fractal->fn = &mandelbrot;
	}
	else if (ft_strequ(name, "burning"))
	{
		fractal->name = "Burning Ship";
		fractal->fn = &burning_ship;
	}
	else if (ft_strequ(name, "julia"))
	{
		fractal->name = "Julia";
		fractal->fn = &julia;
		fractal->interactive = 1;
	}
	else
		error(USAGE_MSG);
}

int				main(int argc, char **argv)
{
	t_mlx_st		mlx;
	t_fractol_st	fractol;
	t_fractal		fractal;
	t_vec2			win_size;

	if (argc < 2 || argc > 4)
		error(USAGE_MSG);
	get_size(argc, &argv[2], &win_size);
	set_fractal(argv[1], &fractal);
	init_fractol(&fractol);
	init_mlx_sess(&mlx);
	fractol.fractal = &fractal;
	mlx.settings.mouse_capture = fractal.interactive;
	mlx.draw_fn = &draw;
	new_window(&mlx, win_size);
	new_canvas(&mlx, win_size);
	zoom_viewport(&mlx.viewport);
	move_viewport(&mlx.viewport, mlx.canvas);
	mlx.datas = (void *)&fractol;
	start_mlx_sess(&mlx);
	return (0);
}
