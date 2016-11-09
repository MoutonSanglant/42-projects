/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 14:58:44 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/08 14:58:44 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <complex.h>
# include <setjmp.h>

# include <libft.h>
# include <libftprintf.h>

# ifdef LINUX
#  include <linux/keybindings.h>
#  include <linux/mlx.h>
#  include <linux/mlx_int.h>
# else
#  include <keybindings.h>
#  include <mlx.h>
# endif

# ifdef BONUS
#  include "bonus/bonus.h"
# endif

# ifdef DEBUG
#  include "debug/debug.h"
# endif

# define PROGRAM_NAME "fractol"
# define PROGRAM_VERSION "1.0"

# define USAGE_MSG "usage: fractol [--help] [fractal ...] [width] [height]"
# define HELP_LINE1 "fractal : fractal to display"
# define HELP_LINE2 "\tjulia\n\tmandelbrot\n\tburning_ship"

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
# define GUI_COLOR WHITE

# define ESCAPE_RADIUS 4.0
# define MAX_ITERATIONS 400

# define DEG(x) (x * 180.0 / M_PI)
# define RAD(x) (x * M_PI / 180.0)

# define EDGE_FN(a, b, c) (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x)
# define MIN3(a, b, c) fminf(a, fmin(b, c))
# define MAX3(a, b, c) fmaxf(a, fmax(b, c))

typedef struct s_fractol_st	t_fractol_st;

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
	double		aspect;
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
	int		draw_gui;
}				t_settings;

typedef enum	e_key_mod
{
	KEY_MODIFIER_SHIFT = 0x1,
	KEY_MODIFIER_CTRL = 0x2
}				t_key_mod;

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

typedef struct	s_key
{
	int		code;
	int		(*fn)(t_mlx_st *, int);
}				t_key;

typedef struct	s_fractal
{
	char	*name;
	int		(*fn)(t_vec2d *, t_vec2d *, int, int);
	int		interactive;
}				t_fractal;

typedef struct	s_colorset
{
	char	*name;
	int		(*fn)(int, t_fractol_st *);
}				t_colorset;

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
**								: keyevent.c :
*/
int				keyevent(t_mlx_st *mlx, int key,
									int (exec)(t_mlx_st *, const t_key *, int));
int				keyevent_ctrl(t_mlx_st *mlx, int key,
									int (exec)(t_mlx_st *, const t_key *, int));
int				keyevent_shift(t_mlx_st *mlx, int key,
									int (exec)(t_mlx_st *, const t_key *, int));

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
int				julia(t_vec2d *z, t_vec2d *c, int depth, int max_depth);
int				mandelbrot(t_vec2d *z, t_vec2d *c, int depth, int max_depth);
int				burning(t_vec2d *z, t_vec2d *c, int depth, int max_depth);

/*
**								 : colorsets.c :
*/
int				colorset_deepblue(int depth, t_fractol_st *fractol);
int				colorset_pastel(int depth, t_fractol_st *fractol);
int				colorset_burning(int depth, t_fractol_st *fractol);
int				colorset_smooth(int depth, t_fractol_st *fractol);

/*
**								 : colorsets_extra.c :
*/
int				colorset_psycho(int depth, t_fractol_st *fractol);
int				colorset_square(int depth, t_fractol_st *fractol);
int				colorset_prismatic(int depth, t_fractol_st *fractol);
int				colorset_parametric(int depth, t_fractol_st *fractol);
int				colorset_parametric_hsl(int depth, t_fractol_st *fractol);

/*
**								 : hsl_to_rgb.c :
*/
void			hsl_to_rgb(t_color *rgb, float h, float sl, float l);

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
********************************************************************************
**								:: Extra ::									   *
********************************************************************************
*/

int				help(void);

void			loop_colorschemes(t_fractol_st *fractol, int modifier);
void			set_colorscheme(t_fractol_st *fractol, int scheme);

#endif
