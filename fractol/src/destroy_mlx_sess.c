/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_mlx_sess.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 10:13:56 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/07 10:13:57 by tdefresn         ###   ########.fr       */
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
