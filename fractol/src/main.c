/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 14:02:46 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/30 15:51:04 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_image	*new_mlx_canvas(t_mlx_st *mlx, t_vec2 size)
{
	t_image		*canvas;

	canvas = (t_image *)ft_memalloc(sizeof(t_image));
	canvas->width = size.x;
	canvas->height = size.y;
	if (!canvas)
		alloc_error("canvas", sizeof(t_image));
	canvas->img = mlx_new_image(mlx->sess, canvas->width, canvas->height);
	if (!canvas->img)
		alloc_error("canvas->img", sizeof(int) * canvas->width * canvas->height);
	canvas->data = mlx_get_data_addr(canvas->img, &canvas->bpp,
										&canvas->sl, &canvas->endian);
	//canvas->filename = filename;
	/*
	mlx->zbuffer = (float *)ft_memalloc(sizeof(float)
											* canvas->width * canvas->height);
	if (!mlx->zbuffer)
		alloc_error("mlx->zbuffer", sizeof(float)
										* canvas->width * canvas->height);
	*/
	return(canvas);
}

/*
static void		init_vertex_grid(t_mlx_st *mlx, t_vert **vertmap,
									int x, int y)
{
	t_mat4x4	trans;
	t_vec3f		loc;

	if (!(mlx->grid = (t_grid *)ft_memalloc(sizeof(t_grid))))
		alloc_error("mlx->grid", sizeof(t_grid));
	if (vertmap)
		init_grid_from_vertmap(mlx->grid, vertmap, x, y);
	else
	{
		ft_putendl_fd("No input file, making a 2x2 flat grid.", 1);
		init_grid(mlx->grid, 2, 2);
	}
	identity_matrix4(&mlx->m_model);
	identity_matrix4(&trans);
	loc.x = -mlx->grid->width * .5f;
	loc.y = -mlx->grid->height * .5f;
	loc.z = 0;
	translation_matrix4(&trans, loc);
	matrix4_product(&trans, &mlx->m_model);
	mlx->options.distance = (int)fmaxf(mlx->grid->width, mlx->grid->height);
}
*/

static void		get_size(int argc, char **argv, t_vec2 *screen_size)
{
	screen_size->x = DEFAULT_WIDTH;
	screen_size->y = DEFAULT_HEIGHT;
	if (argc > 3)
	{
		screen_size->x = ft_atoi(argv[2]);
		screen_size->y = ft_atoi(argv[3]);
		if (screen_size->x < MIN_WIDTH || screen_size->x > MAX_WIDTH)
		{
			ft_putstr_fd("Width must be a value between ", 2);
			ft_putnbr_fd(MIN_WIDTH, 2);
			ft_putstr_fd(" and ", 2);
			ft_putnbr_fd(MAX_WIDTH, 2);
			ft_putchar_fd('\n', 2);
			exit(1);
		}
		if (screen_size->y < MIN_HEIGHT || screen_size->y > MAX_HEIGHT)
		{
			ft_putstr_fd("Height must be a value between ", 2);
			ft_putnbr_fd(MIN_HEIGHT, 2);
			ft_putstr_fd(" and ", 2);
			ft_putnbr_fd(MAX_HEIGHT, 2);
			ft_putchar_fd('\n', 2);
			exit(1);
		}
	}
}

static void		arguments_count_error(void)
{
	ft_putendl_fd(USAGE_MSG, 2);
	exit(1);
}

static void		*get_fractal_fn(char *name)
{
	void	*fn;

	fn = NULL;
	if (ft_strequ(name, "mandelbrot"))
		fn = &draw_mandel;
	else if (ft_strequ(name, "julia"))
		fn = &draw_julia;
	else
	{
		ft_putendl_fd(USAGE_MSG, 2);
		exit(1);
	}
	return (fn);
}

int				main(int argc, char **argv)
{
	t_mlx_st	*mlx;
	t_vec2		screen_size;
	t_fractol_st	fractol_st;
	void		*fract_fn;

	if (argc < 2 || argc > 4)
		arguments_count_error();
	fract_fn = get_fractal_fn(argv[1]);
	get_size(argc, argv, &screen_size);
	set_color_scheme(&fractol_st, 0);
	fractol_st.color.r = 1.f;
	fractol_st.color.g = 1.f;
	fractol_st.color.b = 1.f;
	fractol_st.max_iterations = 25;
	fractol_st.capture_mouse_position = 1;
	fractol_st.hue = .5f;
	fractol_st.saturation = 1.f;
	fractol_st.lightness = .5f;
	fractol_st.damp_hue = 1;
	fractol_st.damp_saturation = 1;
	fractol_st.damp_lightness = 1;
	mlx = new_mlx_sess();
	mlx->draw_fn = fract_fn;
	mlx->name = ft_strdup("Fract'ol");
	mlx->datas = (void *)&fractol_st;
	mlx->canvas = new_mlx_canvas(mlx, screen_size);
	mlx->viewport.zoom_level = 1.f;
	mlx->viewport.pos.x = 0;
	mlx->viewport.pos.y = 0;
	mlx->viewport.size.x = 2.f;
	mlx->viewport.size.y = 2.f;
	mlx->modifiers.shift = 0;
	mlx->modifiers.ctrl = 0;
	init_mlx_sess(mlx);
	start_mlx_sess(mlx);
	return (0);
}
