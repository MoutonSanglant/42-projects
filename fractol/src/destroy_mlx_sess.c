/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_mlx_mlx.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 12:09:25 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/06 14:13:29 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	destroy_mlx_sess(t_mlx_st *mlx)
{
	mlx_destroy_image(mlx->sess, mlx->canvas->img);
	mlx_destroy_window(mlx->sess, mlx->win);
	ft_memdel((void **)&mlx->canvas);
	ft_memdel((void **)&mlx->sess);
	ft_memdel((void **)&mlx->name);
}
