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

# define MAX_ITERATIONS 100

# ifdef BONUS
#  include <float.h>
#  include <sys/time.h>
#  include <limits.h>

/*
** FPS in microseconds
** 16666 for 60 fps
** 33332 for 30 fps
*/
#  define FPS 33332
# endif

# ifdef LINUX
#  include "../includes/linux/mlx.h"
#  include "../includes/linux/mlx_int.h"

#  define KEYPRESS		KeyPress
#  define KEYRELEASE	KeyRelease
#  define MOTIONNOTIFY	MotionNotify
#  define DESTROYNOTIFY	DestroyNotify
#  define KEYPRESSMASK		KeyPressMask
#  define KEYRELEASEMASK	KeyReleaseMask
#  define POINTERMOTIONMASK	PointerMotionMask

#  define KEY_ESCAPE	65307
#  define KEY_STAR		30
#  define KEY_NUMPAD_MORE	65451
#  define KEY_NUMPAD_LESS	65453
#  define KEY_NUMPAD_STAR	65450
#  define KEY_NUMPAD_SLASH	11111
#  define KEY_0		224
#  define KEY_1		38
#  define KEY_2		233
#  define KEY_3		34
#  define KEY_4		39
#  define KEY_5		40
#  define KEY_6		45
#  define KEY_7		232
#  define KEY_8		95
#  define KEY_9		231
#  define KEY_A		113
#  define KEY_B		98
#  define KEY_D		100
#  define KEY_E		101
#  define KEY_F		102
#  define KEY_G		111111
#  define KEY_H		104
#  define KEY_I		105
#  define KEY_R		111111
#  define KEY_O		111
#  define KEY_P		112
#  define KEY_Q		97
#  define KEY_R		111111
#  define KEY_S		115
#  define KEY_W		122
#  define KEY_Z		119
#  define KEY_TAB	111111
#  define KEY_LEFT	65361
#  define KEY_RIGHT	65363
#  define KEY_UP	65362
#  define KEY_DOWN	65364
#  define KEY_PAGE_UP	65365
#  define KEY_PAGE_DOWN	65366

#  define KEY_LEFT_CTRL		25600
#  define KEY_LEFT_SHIFT	25700
#  define KEY_RIGHT_SHIFT	25800
#  define KEY_RIGHT_CTRL	26900

#  define MOUSE_CLICK_LEFT	1
#  define MOUSE_CLICK_RIGHT	2
#  define MOUSE_SCROLL_DOWN	4
#  define MOUSE_SCROLL_UP	5

# else
#  include "../includes/mlx.h"
#  define KEYPRESS		2
#  define KEYRELEASE	3
#  define MOTIONNOTIFY	6
#  define DESTROYNOTIFY	17
#  define KEYPRESSMASK		(1L<<0)
#  define KEYRELEASEMASK	(1L<<1)
#  define POINTERMOTIONMASK	(1L<<6)

#  define KEY_ESCAPE	53
#  define KEY_STAR		30
#  define KEY_NUMPAD_MORE	69
#  define KEY_NUMPAD_LESS	78
#  define KEY_NUMPAD_STAR	67
#  define KEY_NUMPAD_SLASH	75
#  define KEY_0		29
#  define KEY_1		18
#  define KEY_2		19
#  define KEY_3		20
#  define KEY_4		21
#  define KEY_5		23
#  define KEY_6		22
#  define KEY_7		26
#  define KEY_8		28
#  define KEY_9		25
#  define KEY_A		0
#  define KEY_B		11
#  define KEY_D		2
#  define KEY_E		14
#  define KEY_F		3
#  define KEY_G		5
#  define KEY_H		4
#  define KEY_I		34
#  define KEY_L		37
#  define KEY_O		31
#  define KEY_P		35
#  define KEY_Q		12
#  define KEY_R		15
#  define KEY_S		1
#  define KEY_W		13
#  define KEY_Z		6
#  define KEY_TAB	48
#  define KEY_LEFT	123
#  define KEY_RIGHT	124
#  define KEY_UP	126
#  define KEY_DOWN	125
#  define KEY_PAGE_UP		116
#  define KEY_PAGE_DOWN		121

#  define KEY_LEFT_CTRL		256
#  define KEY_LEFT_SHIFT	257
#  define KEY_RIGHT_SHIFT	258
#  define KEY_RIGHT_CTRL	269

#  define MOUSE_CLICK_LEFT	1
#  define MOUSE_CLICK_RIGHT	2
#  define MOUSE_SCROLL_DOWN	4
#  define MOUSE_SCROLL_UP	5

# endif

# define DEG(x) (x * 180.0 / M_PI)
# define RAD(x) (x * M_PI / 180.0)

# define EDGE_FN(a, b, c) (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x)
# define MIN3(a, b, c) fminf(a, fmin(b, c))
# define MAX3(a, b, c) fmaxf(a, fmax(b, c))

/*
**	Matrices are in row-major columns
*/
typedef float	t_mat4x4[16];

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


typedef struct	s_vec3f
{
	float		x;
	float		y;
	float		z;
}				t_vec3f;

typedef struct	s_vec4f
{
	float		x;
	float		y;
	float		z;
	float		w;
}				t_vec4f;

typedef struct	s_color
{
	float		r;
	float		g;
	float		b;
}				t_color;

typedef struct	s_vert
{
	t_vec3f		coord;
	t_color		color;
}				t_vert;

typedef t_vert	t_tri[3];

typedef struct	s_grid
{
	int		width;
	int		height;
	t_tri	*triangles;
}				t_grid;

typedef struct	s_camera
{
	float	angle_of_view;
	float	aspect;
	float	far;
	float	near;
	float	top;
	float	bottom;
	float	left;
	float	right;
}				t_camera;

typedef struct	s_options // settings
{
	int				zdraw;
	int				distance;
	int				tooltip;

	int				bg_color; // fill_color

	// TODO
	// discard:
	float			map_height;
	float			line_width;
	int				lines_color;
	int				faces_color;
	int				fill_faces;
}				t_options;

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
}				t_image;

/*
**  viewport range is [-1, 1]
*/

typedef struct	s_viewport
{
	t_vec2f		pos;
	t_vec2f		size;
	double		zoom_level;
}				t_viewport;

typedef struct	s_fractol_st t_fractol_st;

struct			s_fractol_st
{
	char	*name;
	int		(*color_fn)(int, t_fractol_st *);
	char	*colorset_name;
	int		max_iterations;
	t_color	color;
	int		capture_mouse_position;
	double	hue;
	double	saturation;
	double	lightness;
	int		damp_hue;
	int		damp_saturation;
	int		damp_lightness;
};

typedef struct	s_key_modifiers
{
	int		shift;
	int		ctrl;
}				t_key_modifiers;

typedef struct	s_mlx_st
{
	void			*name;
	void			*sess;
	void			*win;
	t_image			*canvas;
	float			*zbuffer;

	void			*datas;
	t_viewport		viewport;

	void			(*draw_fn)(struct s_mlx_st *);
	t_vec2d			mouse_pos;
	t_key_modifiers		modifiers;

	t_camera		camera;
	t_mat4x4		*world;
	t_mat4x4		*view;
	t_mat4x4		*projection;
	t_mat4x4		*world_to_camera;
	t_mat4x4		m_model;
	t_options		options;
	struct timeval	last_tval;
	int				need_update;
	int				system_endian;

	// TODO
	// discard:
	t_grid			*grid;
}				t_mlx_st;

typedef struct	s_bresenham
{
	t_vec2ui32	xy;
	int			e;
	int			x1;
	int			x2;
	int			y1;
	int			y2;
	int			dx;
	int			dy;
	int			incx;
	int			incy;
	int			inc1;
	int			inc2;
}				t_bresenham;

typedef struct	s_tree
{
	int	degree;
}				t_tree;

// TODO:
// Survey
float			hex_to_float(char *hex);


/*
**	RENDERING
*/
void			draw_3dgrid(t_mlx_st *mlx);
void			rasterize(t_mlx_st *p, t_tri *triangle);

/*
**	DRAWING
*/
void			bresenham_draw_line(t_mlx_st *mlx, t_vec2 *from, t_vec2 *to);
void			draw_square(t_mlx_st *mlx, int color,
							t_vec2f *from, t_vec2f *to);
void			draw_gui(t_mlx_st *mlx);
//void			draw_image(t_mlx_st *mlx);
void			draw_image(t_mlx_st *mlx, void *img, int *x, int *y);

void			clear_canvas(t_mlx_st *mlx, int color);
void			set_image_pixel(t_mlx_st *mlx, t_image *img, int color,
								t_vec2ui32 *xy);

/*
**	INIT
*/
void			init_grid(t_grid *grid, int width, int height);
void			init_grid_from_vertmap(t_grid *grid, t_vert **vertmap,
										int width, int height);


/*
********************************************************************************
**								  :: MLX ::									   *
********************************************************************************
*/

/*
**							: new_mlx_sess.c :
*/
t_mlx_st		*new_mlx_sess();

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

void			zoom_in(t_mlx_st *mlx, int x, int y);
void			zoom_out(t_mlx_st *mlx, int x, int y);

/*
********************************************************************************
**								:: Matrices ::								   *
********************************************************************************
*/

/*
**								 : matrix.c :
*/
void			translation_matrix4(t_mat4x4 *mat, t_vec3f vec);
void			scaling_matrix4(t_mat4x4 *mat, t_vec3f vec);
void			rotation_x_matrix4(t_mat4x4 *mat, float alpha);
void			rotation_y_matrix4(t_mat4x4 *mat, float alpha);
void			rotation_z_matrix4(t_mat4x4 *mat, float alpha);
/*
**							: projection_matrix.c :
*/
void			perspective_projection_matrix4(t_mat4x4 *mat, t_camera *camera);
void			orthographic_projection_matrix4(t_mat4x4 *mat,
												t_camera *camera);
/*
**							 : identity_matrix.c :
*/
void			identity_matrix4(t_mat4x4 *mat);
/*
**							 : inverse_matrix.c :
*/
void			inverse_matrix4(t_mat4x4 *in_mat, t_mat4x4 *out_mat);
/*
**							  : matrix_math.c :
*/
void			copy_matrix4(t_mat4x4 *dst, const t_mat4x4 *src);
void			transpose_matrix4(t_mat4x4 *mat);
void			matrix4_product(t_mat4x4 *mat_b, t_mat4x4 *out);
t_vec3f			apply_matrix4(t_vec3f vec, t_mat4x4 *mat);

/*
********************************************************************************
**								 :: Camera ::								   *
********************************************************************************
*/

/*
**								: camera.c :
*/
void			camera(t_mlx_st *mlx, char *str);

/*
********************************************************************************
**								:: Fractals ::								   *
********************************************************************************
*/

/*
**								 : draw_mandel.c :
*/
void			draw_mandel();

/*
**								 : draw_julia.c :
*/
void			draw_julia();

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
t_color			hsl_to_rgb(double h, double sl, double l);

/*
********************************************************************************
**								:: Errors ::								   *
********************************************************************************
*/

/*
**							  : alloc_error.c :
*/
void			alloc_error(char *error_obj, size_t alloc_size);

/*
**	EXTRA
*/

void			set_color_scheme(t_fractol_st *fractol, int scheme);
void			change_grid_z(t_grid *grid, float factor);

# ifdef DEBUG

void			output_image_info(t_image *image);
void			draw_debug_gui(t_mlx_st *mlx);
# endif
#endif
