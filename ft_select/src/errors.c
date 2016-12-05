/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 19:55:43 by tdefresn          #+#    #+#             */
/*   Updated: 2016/12/05 08:47:07 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "ft_select.h"

void	quit(void)
{
	termios_if(&termios_release);
	exit (1);
}

void	fatal(char *format, ...)
{
	va_list	ap;

	va_start(ap, format);
	ft_eprintf("%s: ", PROGRAM_NAME);
	ft_veprintf(format, &ap);
	write(1, "\n", 1);
	va_end(ap);
	quit();
}
