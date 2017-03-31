/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 19:23:43 by tdefresn          #+#    #+#             */
/*   Updated: 2017/03/22 14:32:22 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <libftprintf.h>

#include "philo.h"

/*
void	error(int error, char *description)
{
	ft_putstr_fd(PGM_NAME, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" (error: ", 2);
	ft_putnbr_fd(err, 2);
	ft_putendl_fd(")", 2);
	exit (err);
}
*/

static void	usage(void)
{
	ft_eprintf(STR_USAGE);
	exit(ERRNO_USAGE);
}

void		thread_error(int error, int errno)
{
	(void)error;
	ft_eprintf("Thread error: %i\n", errno);
}

void		error(int error, const char *description)
{
	if (error == ERRNO_USAGE)
		usage();
	ft_putstr_fd("Error: ", 2);
	if (error == ERRNO_THREAD_CREATE)
		ft_eprintf("%s (%s)\n", ERR_THREAD_CREATE, description);
	else
		ft_putendl_fd(ERR_UNDEFINED, 2);
	exit(error);
}
