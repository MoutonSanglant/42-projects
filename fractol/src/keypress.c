/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 14:14:47 by tdefresn          #+#    #+#             */
/*   Updated: 2016/12/06 16:13:39 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	exec_keyevent(t_mlx_st *mlx, const t_key *key_list, int key)
{
	int		i;

	i = 0;
	while (key_list[i].fn != NULL)
	{
		if (key == key_list[i].code)
			key_list[i].fn(mlx, key);
		i++;
	}
	mlx->need_update = 1;
	return (1);
}

int			keypress(int key, void *p)
{
	t_mlx_st	*mlx;

	mlx = (t_mlx_st *)p;
	mlx->key_modifiers |= (key == KEY_LEFT_SHIFT || key == KEY_RIGHT_SHIFT)
		? KEY_MODIFIER_SHIFT : 0;
	mlx->key_modifiers |= (key == KEY_LEFT_CTRL || key == KEY_RIGHT_CTRL)
		? KEY_MODIFIER_CTRL : 0;
	if (mlx->key_modifiers & KEY_MODIFIER_CTRL)
		return (keyevent_ctrl(mlx, key, &exec_keyevent));
	else if (mlx->key_modifiers & KEY_MODIFIER_SHIFT)
		return (keyevent_shift(mlx, key, &exec_keyevent));
	else
		return (keyevent(mlx, key, &exec_keyevent));
	return (0);
}
