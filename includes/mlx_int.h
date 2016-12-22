/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_int.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 19:59:35 by tdefresn          #+#    #+#             */
/*   Updated: 2016/12/04 19:59:35 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** mlx_int.h for minilibx
** --------------
** ol@staff.42.fr
** --------------
** include opengl needed before mlx_int.h
*/

#ifndef MLX_INT_H

# define MLX_INT_H

# define MAX_EVENT		32
# define MAX_PIXEL_NB	200000
# define UNIQ_BPP		4

# define FONT_WIDTH		10
# define FONT_HEIGHT	20

/*
** structs
*/

int		mlx_shaders(glsl_info_t *glsl);
char	**mlx_int_str_to_wordtab(char *str);
int		mlx_int_str_str(char *str, char *find, int len);
int		mlx_int_str_str_cote(char *str, char *find, int len);
int		mlx_destroy_image(mlx_ptr_t *mlx_ptr, mlx_img_list_t *img_ptr);
void	*mlx_new_image();
void	*mlx_xpm_to_image(mlx_ptr_t *xvar, char **xpm_data, int *width,
																int *height);
int		mlx_do_sync(mlx_ptr_t *mlx_ptr);

#endif
