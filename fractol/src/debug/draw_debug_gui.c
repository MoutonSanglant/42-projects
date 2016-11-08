/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_debug_gui.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 14:41:41 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/08 00:41:14 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

static char		*strjoinat(const char *s1, const char *s2, int idx)
{
	char *dst;

	dst = ft_strdup(s1);
	dst[idx] = '\0';
	dst = ft_strcat(dst, s2);
	return (dst);
}

static void		draw_image_info(void *s, void *w, t_image *img, int *l)
{
	static char	*addr = NULL;
	static char	*bpp = NULL;
	static char	*sl = NULL;
	static char	*endianess = NULL;

	*l = *l - 1;
	if (!addr || !bpp || !sl || !endianess)
	{
		addr = strjoinat("Address:   0x             ",
				ft_itoa_base((uintptr_t)img->data, 16), 13);
		bpp = strjoinat("BPP:             ", ft_itoa(img->bpp), 11);
		sl = strjoinat("Line size:             ", ft_itoa(img->sl), 11);
		endianess = strjoinat("Endianess:        ", ft_itoa(img->endian), 11);
	}
	if (img->filename)
	{
		*l = *l + 1;
		mlx_string_put(s, w, 30, *l * GUI_LINE_HEIGHT, WHITE, "Source file: ");
		mlx_string_put(s, w, 155, *l * GUI_LINE_HEIGHT, WHITE, img->filename);
	}
	mlx_string_put(s, w, 30, (*l += 1) * GUI_LINE_HEIGHT, WHITE, addr);
	mlx_string_put(s, w, 30, (*l += 1) * GUI_LINE_HEIGHT, WHITE, bpp);
	mlx_string_put(s, w, 30, (*l += 1) * GUI_LINE_HEIGHT, WHITE, sl);
	mlx_string_put(s, w, 30, (*l += 1) * GUI_LINE_HEIGHT, WHITE, endianess);
	*l = *l + 1;
}

void			draw_debug_gui(t_mlx_st *mlx)
{
	void	*s;
	void	*w;
	int		line;

	line = 0;
	s = mlx->sess;
	w = mlx->win;
	mlx_string_put(s, w, 5, line++ * GUI_LINE_HEIGHT,
								0x00ffffff, "DEBUG CONSOLE");
	mlx_string_put(s, w, 5, line++ * GUI_LINE_HEIGHT, 0x00ffffff, "Image");
	draw_image_info(s, w, mlx->canvas, &line);
	mlx_string_put(s, w, 5, line++ * GUI_LINE_HEIGHT, 0x00ffffff, "Camera");
}
