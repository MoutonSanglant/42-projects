/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_mlx_mlx.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 12:09:25 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/11 13:18:50 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	destroy_mlx_sess(t_mlx_st *mlx)
{
	mlx_destroy_image(mlx->sess, mlx->canvas->img);
	mlx_destroy_window(mlx->sess, mlx->win);
	//ft_memdel((void **)&mlx->zbuffer);
	//ft_memdel((void **)&mlx->world);
	//ft_memdel((void **)&mlx->view);
	//ft_memdel((void **)&mlx->world_to_camera);
	//ft_memdel((void **)&mlx->projection);
	//ft_memdel((void **)&mlx->grid->triangles);
	//ft_memdel((void **)&mlx->grid);
	//ft_memdel((void **)&mlx->datas);
	ft_memdel((void **)&mlx->canvas);
	ft_memdel((void **)&mlx->sess);
	ft_memdel((void **)&mlx->name);
	ft_memdel((void **)&mlx);
}
