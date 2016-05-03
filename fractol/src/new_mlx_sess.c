/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_mlx_sess.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 23:57:56 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/03 23:57:57 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_mlx_st	*new_mlx_sess()
{
	t_mlx_st	*mlx;

	if (!(mlx = (t_mlx_st *)ft_memalloc(sizeof(t_mlx_st))))
		alloc_error("mlx", sizeof(t_mlx_st));
	if (!(mlx->sess = mlx_init()))
	{
		ft_memdel((void **)&mlx);
		alloc_error("mlx->sess", sizeof(t_mlx_st));
	}
	return (mlx);
}
