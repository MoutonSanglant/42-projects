/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/14 12:15:46 by tdefresn          #+#    #+#             */
/*   Updated: 2016/09/17 22:16:56 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	error(void)
{
	ft_putendl("error");
	exit(1);
}

void	memory_error(void)
{
	ft_putendl("error (memory)");
	exit(2);
}

void	grid_size_error()
{
	ft_putendl("error (grid is bigger than 8x8)");
	exit(3);
}

void	buffer_error(char *buffer)
{
	ft_memdel((void **)&buffer);
	error();
}
