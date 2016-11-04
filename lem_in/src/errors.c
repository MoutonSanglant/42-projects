/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/14 12:15:46 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/04 09:40:47 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "lem_in.h"

void	error(char *str)
{
	ft_putendl("ERROR");
	ft_putstr_fd("lem-in: ", 2);
	ft_putendl_fd(str, 2);
	exit(1);
}

void	memerror(void)
{
	ft_putendl("ERROR");
	perror("lem_in");
	exit(2);
}
