/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 18:17:53 by tdefresn          #+#    #+#             */
/*   Updated: 2017/03/17 18:17:53 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <libft.h>
# include <libftprintf.h>

# ifdef LINUX
#  include <GL/glew.h>
# endif

# include <GLFW/glfw3.h>

# include "vector.h"
//# include "matrix.h"
# include "linmath.h"

# define OPTIONS_COUNT 3

# define WIN_WIDTH 640
# define WIN_HEIGHT 480

# define ERRNO_USAGE 1
# define ERRNO_COLOR 2

# define STR_USAGE "rtv1 [-w width] [-h height]\n"
# define ERR_COLOR "invalid color"
# define ERR_UNDEFINED "undefined error"

typedef enum	e_flags
{
	FLAG_NONE	= 0x0,
	FLAG_WIDTH	= 0x1,
	FLAG_HEIGHT	= 0x2
}				t_flags;

typedef struct	s_option
{
	char	*l;
	t_flags	f;
	char	s;
}				t_option;

typedef struct	s_rt
{
	t_flags	flags;
	int		width;
	int		height;
}				t_rt;

/*
** == errors.c
*/

void		error(int error, char *description);
void		error_glfw(int error, const char *description);

/*
** == options.c
*/

void		match_options(char *arg, t_flags *flags);

/*
** == arguments.c
*/

void		parse_arguments(int count, char **arguments, t_rt *rt);

/*
** == input.c
*/

void	key_callback(GLFWwindow *win, int key, int code, int action, int mods);

#endif
