/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 01:00:57 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/26 15:52:34 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <complex.h>
# include <setjmp.h>

# include <libft.h>
# include <libftprintf.h>
# include <keybindings.h>

# define PROGRAM_NAME "fdf"

// TODO
# define USAGE_MSG "usage: fractol [mandelbrot | julia | ...] [width] [height]"

# define BUFF_SIZE 32
# define BLACK	0x00000000
# define WHITE	0x00ffffff
# define RED	0x00ff0000
# define GREEN	0x0000ff00
# define BLUE	0x000000ff
# define DEFAULT_WIDTH	800
# define DEFAULT_HEIGHT	600
# define MIN_WIDTH	100
# define MAX_WIDTH	1600
# define MIN_HEIGHT	100
# define MAX_HEIGHT	900
# define GUI_LINE_HEIGHT 18

# define ESCAPE_RADIUS 2000000000000000000000000000000000000000000000000000000.0
# define MAX_ITERATIONS 1000

# ifdef BONUS
#  include <float.h>
#  include <sys/time.h>
#  include <limits.h>

/*
** FPS in microseconds
** 16666 for 60 fps
** 33332 for 30 fps
*/
#  define FPS_LIMIT 33332
# endif

# define DEG(x) (x * 180.0 / M_PI)
# define RAD(x) (x * M_PI / 180.0)

# define EDGE_FN(a, b, c) (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x)
# define MIN3(a, b, c) fminf(a, fmin(b, c))
# define MAX3(a, b, c) fmaxf(a, fmax(b, c))

typedef struct	s_vec2
{
	int			x;
	int			y;
}				t_vec2;

typedef struct	s_vec2ui32
{
	uint32_t	x;
	uint32_t	y;
}				t_vec2ui32;

typedef struct	s_vec2f
{
	float		x;
	float		y;
}				t_vec2f;

typedef struct	s_vec2d
{
	double		x;
	double		y;
}				t_vec2d;

typedef struct	s_color
{
	float		r;
	float		g;
	float		b;
}				t_color;

typedef struct	s_image
{
	void		*img;
	char		*data;
	char		*filename;
	int			sl;
	int			bpp;
	int			endian;
	uint32_t	width;
	uint32_t	height;
	float		aspect;
}				t_image;

/*
**  viewport range is [-1, 1]
*/

typedef struct	s_viewport
{
	t_vec2d		pos;
	t_vec2d		range;
	t_vec2d		size;
	t_vec2d		min;
	t_vec2d		max;
	t_vec2d		step;
	double		zoom_level;
}				t_viewport;

typedef struct	s_settings
{
	int		zdraw;
	int		distance;
	int		tooltip;
	int		fill_color;
	int		mouse_capture;
}				t_settings;

typedef struct	s_mlx_st
{
	void			*name;
	void			*sess;
	void			*win;
	void			*datas;
	void			(*draw_fn)(struct s_mlx_st *);
	t_image			*canvas;
	t_viewport		viewport;
	t_vec2d			mouse_pos;
	t_key_mod		key_modifiers;
	t_settings		settings;
	struct timeval	last_tval;
	int				need_update;
	int				system_endian;

}				t_mlx_st;

typedef struct	s_fractal
{
	char	*name;
	int		(*fn)(double, double, int);
	int		interactive;
}				t_fractal;

typedef struct	s_fractol_st t_fractol_st;

struct			s_fractol_st
{
	t_fractal	*fractal;
	char		*colorset_name;
	int			(*color_fn)(int, t_fractol_st *);
	int			iterations;
	t_color		color;
	double		hue;
	double		saturation;
	double		lightness;
	int			damp_hue;
	int			damp_saturation;
	int			damp_lightness;
	int			negative;
};

/*
**	DRAWING
*/
void			draw_gui(t_mlx_st *mlx);
void			set_image_pixel(t_mlx_st *mlx, t_image *img, int color,
								t_vec2ui32 *xy);
void			init_fractol(t_fractol_st *fractol);

/*
********************************************************************************
**								  :: MLX ::									   *
********************************************************************************
*/

/*
**							: init_mlx_st.c :
*/
void			init_mlx_sess(t_mlx_st *mlx);
/*
**							: start_mlx_st.c :
*/
void			start_mlx_sess(t_mlx_st *mlx);
/*
**						   : destroy_mlx_sess.c :
*/
void			destroy_mlx_sess(t_mlx_st *mlx);

void			new_canvas(t_mlx_st *mlx, t_vec2 screen_size);
void			new_window(t_mlx_st *mlx, t_vec2 screen_size);

/*
********************************************************************************
**							 :: Window events ::							   *
********************************************************************************
*/

/*
**								: expose.c :
*/
int				expose(void *p);

/*
**							   : draw_loop.c :
*/
int				draw_loop(void *p);

/*
**							   : draw.c :
*/
int				draw_loop(void *p);
void			draw(t_mlx_st *mlx);

/*
********************************************************************************
**							  :: Input events ::							   *
********************************************************************************
*/

/*
**								: keypress.c :
*/
int				keypress(int key, void *p);

/*
**								: keypress.c :
*/
int				keyrelease(int key, void *p);

/*
**								: mouse_event.c :
*/
int				mouse_click_event(int button, int x, int y, void *p);
int				mouse_motion_event(int x, int y, void *p);

/*
********************************************************************************
**							  :: Viewport ::								   *
********************************************************************************
*/

/*
**								: viewport.c :
*/
void			move_viewport(t_viewport *viewport, t_image *canvas);
void			zoom_viewport(t_viewport *viewport);

/*
**								: zoom.c :
*/
void			zoom_in(t_mlx_st *mlx, int x, int y);
void			zoom_out(t_mlx_st *mlx, int x, int y);

/*
********************************************************************************
**								:: Fractals ::								   *
********************************************************************************
*/

/*
**								 : mandelbrot.c :
*/
//int				mandelbrot(double c1, double c2, int max_depth);
int				mandelbrot(double c1, double c2, int max_depth);
int				julia(double c1, double c2, int max_depth);
int				burning_ship(double c1, double c2, int max_depth);

/*
**								 : colorsets.c :
*/
int				colorset_deepblue(int depth, t_fractol_st *fractol_st);
int				colorset_greyradiosity(int depth, t_fractol_st *fractol_st);
int				colorset_burning(int depth, t_fractol_st *fractol_st);
int				colorset_smooth(int depth, t_fractol_st *fractol_st);

/*
**								 : colorsets_extra.c :
*/
int				colorset_psycho(int depth, t_fractol_st *fractol_st);
int				colorset_square(int depth, t_fractol_st *fractol_st);
int				colorset_prismatic(int depth, t_fractol_st *fractol_st);
int				colorset_parametric(int depth, t_fractol_st *fractol_st);
int				colorset_parametric_hsl(int depth, t_fractol_st *fractol_st);

/*
**								 : hsl_to_rgb.c :
*/
t_color			hsl_to_rgb(float h, float sl, float l, int negative);

/*
********************************************************************************
**								:: Errors ::								   *
********************************************************************************
*/

/*
**							  : error.c :
*/
void			error(char *str);
void			alloc_error(char *error_obj, size_t alloc_size);

/*
**	EXTRA
*/

void			set_color_scheme(t_fractol_st *fractol, int scheme);

# ifdef DEBUG

void			draw_debug_gui(t_mlx_st *mlx);
# endif
#endif
