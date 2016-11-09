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

# include <libft.h>
# include <keybindings.h>

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

# define USAGE_MSG "Usage: fdf [Path] [Width] [Height]"

# define BUFF_SIZE 32
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

typedef struct	s_image
{
	void	*img;
	char	*data;
	char	*filename;
	int		sl;
	int		bpp;
	int		endian;
}				t_image;

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

typedef struct	s_options
{
	float			map_height;
	float			line_width;
	int				bresenham;
	int				zdraw;
	int				fill_faces;
	int				lines_color;
	int				faces_color;
	int				bg_color;
	int				distance;
	int				tooltip;
}				t_options;

typedef struct	s_mlx_sess
{
	uint32_t		width;
	uint32_t		height;
	void			*sess;
	void			*win;
	t_image			*img;
	float			*zbuffer;
	t_grid			*grid;
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
}				t_mlx_sess;

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

/*
**	FILES
*/

int				count_file_lines(char *path);
t_vert			**get_vertmap_from_file(char *path, int *x, int *y);

/*
**	MLX
*/

t_mlx_sess		*init_mlx_sess();
void			start_mlx_sess(t_mlx_sess *sess);
void			destroy_mlx_sess(t_mlx_sess	*sess);
float			hex_to_float(char *hex);

/*
**	RENDERING
*/

void			draw_3dgrid(t_mlx_sess *sess);
void			rasterize(t_mlx_sess *p, t_tri *triangle);

/*
**	LOOPS
*/

int				draw_loop(void *p);

/*
**	DRAWING
*/

void			bresenham_draw_line(t_mlx_sess *sess, t_vec2 *from, t_vec2 *to);
void			draw_square(t_mlx_sess *sess, int color,
							t_vec2f *from, t_vec2f *to);
void			draw_picture(t_mlx_sess *sess);

void			clear_canvas(t_mlx_sess *sess, int color);
void			set_image_pixel(t_mlx_sess *sess, t_image *img, int color,
								t_vec2ui32 *xy);

/*
**	INIT
*/

void			init_grid(t_grid *grid, int width, int height);
void			init_grid_from_vertmap(t_grid *grid, t_vert **vertmap,
										int width, int height);

/*
**	MATRIX
*/

void			identity_matrix4(t_mat4x4 *mat);
void			inverse_matrix4(t_mat4x4 *in_mat, t_mat4x4 *out_mat);
void			translation_matrix4(t_mat4x4 *mat, t_vec3f vec);
void			scaling_matrix4(t_mat4x4 *mat, t_vec3f vec);
void			rotation_x_matrix4(t_mat4x4 *mat, float alpha);
void			rotation_y_matrix4(t_mat4x4 *mat, float alpha);
void			rotation_z_matrix4(t_mat4x4 *mat, float alpha);
void			perspective_projection_matrix4(t_mat4x4 *mat, t_camera *camera);
void			orthographic_projection_matrix4(t_mat4x4 *mat,
												t_camera *camera);

void			copy_matrix4(t_mat4x4 *dst, const t_mat4x4 *src);
void			transpose_matrix4(t_mat4x4 *mat);
void			matrix4_product(t_mat4x4 *mat_b, t_mat4x4 *out);
t_vec3f			apply_matrix4(t_vec3f vec, t_mat4x4 *mat);

/*
**	CAMERAS
*/

void			camera(t_mlx_sess *sess, char *str);

/*
**	WINDOW EVENTS
*/

int				expose(void *p);

/*
**	INPUT EVENTS
*/

int				keydown(int key, void *p);
int				keypress(int key, void *p);

/*
**	GNL
*/
typedef struct	s_parser
{
	int		fd;
	long	bs;
	char	*buf;
}				t_parser;

int				get_next_line(int const fd, char **line);

/*
**	ERRORS
*/

void			alloc_error(char *error_obj, size_t alloc_size);
void			format_error(void);

/*
**	EXTRA
*/

void			set_color_scheme(t_mlx_sess *sess, int lines_color,
									int faces_color, int bg_color);
void			change_grid_z(t_grid *grid, float factor);

# ifdef DEBUG

void			output_image_info(t_image *image);
void			draw_debug_gui(t_mlx_sess *sess);
# endif
#endif
