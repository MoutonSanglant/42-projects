/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:30:12 by tdefresn          #+#    #+#             */
/*   Updated: 2017/03/21 20:17:24 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "rtv1.h"

static void	usage(void)
{
	ft_eprintf(STR_USAGE);
	exit(ERRNO_USAGE);
}

void		error_glfw(int error, const char *description)
{
	(void)error;
	ft_eprintf("Error: %s\n", description);
}

void		error(int error, const char *description)
{
	if (error == ERRNO_USAGE)
		usage();
	ft_putstr_fd("Error: ", 2);
	if (error == ERRNO_COLOR)
		ft_eprintf("%s (%s)\n", ERR_COLOR, description);
	else
		ft_putendl_fd(ERR_UNDEFINED, 2);
	exit(error);
}
