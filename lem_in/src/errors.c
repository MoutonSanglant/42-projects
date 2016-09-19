/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/14 12:15:46 by tdefresn          #+#    #+#             */
/*   Updated: 2016/09/18 15:47:20 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	error(char *str)
{
	ft_putendl("ERROR");
	ft_putstr_fd("lem-in: ", 2);
	ft_putendl_fd(str, 2);
	exit(1);
}

void	memory_error(void)
{
	ft_putendl("ERROR");
	ft_putendl_fd("lem-in: memory error", 2);
	exit(2);
}
