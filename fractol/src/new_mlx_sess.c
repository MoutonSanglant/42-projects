/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_mlx_sess.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 20:30:19 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/03 20:32:19 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_mlx_sess	*new_mlx_sess()
{
	t_mlx_sess	*sess;

	if (!(sess = (t_mlx_sess *)ft_memalloc(sizeof(t_mlx_sess))))
		alloc_error("sess", sizeof(t_mlx_sess));
	if (!(sess->sess = mlx_init()))
	{
		ft_memdel((void **)&sess);
		alloc_error("sess->sess", sizeof(t_mlx_sess));
	}
	return (sess);
}
