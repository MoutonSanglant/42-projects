/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:30:12 by tdefresn          #+#    #+#             */
/*   Updated: 2017/09/10 00:30:06 by mouton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

#include <stdlib.h>
#include <libftprintf.h>

void		error(t_errno errno, const char *description)
{
	if (errno == ERRNO_USAGE)
		ft_eprintf("%s\n", STR_USAGE);
	else
		ft_eprintf("Error: ");
	if (errno == ERRNO_MEMORY)
		ft_eprintf("%s (%s)\n", ERR_MEMORY, description);
	else if (errno == ERRNO_OPEN)
		ft_eprintf("%s (%s)\n", ERR_OPEN, description);
	else if (errno == ERRNO_READ)
		ft_eprintf("%s (%s)\n", ERR_READ, description);
	else if (errno == ERRNO_MULTIPLE_WIDTH)
		ft_eprintf("%s\n", ERR_MULTIPLE_WIDTH);
	else if (errno == ERRNO_MULTIPLE_HEIGHT)
		ft_eprintf("%s\n", ERR_MULTIPLE_HEIGHT);
	else
		ft_eprintf("%s\n", ERR_UNDEFINED);
	exit(errno);
}
