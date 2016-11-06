/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 13:58:21 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/06 14:35:22 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	error(char *str)
{
	ft_eprintf("%s: %s\n", PROGRAM_NAME, str);
	exit(1);
}

void	alloc_error(char *error_obj, size_t alloc_size)
{
	ft_putstr_fd("Memory allocation error: ", 2);
	ft_putstr_fd(error_obj, 2);
	ft_putstr_fd(" required a block of size ", 2);
	ft_putnbr_fd(alloc_size, 2);
	ft_putendl_fd(" but couldn't get it.'", 2);
	exit(1);
}
