/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 14:25:27 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/13 20:58:42 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_select.h"

void	sig_handler(int signo)
{
	if (signo == SIGINT)
		ft_printf("Hello SIGINT !\n");
	if (signo == SIGQUIT)
		ft_printf("Hello SIGQUIT !\n");
	termios_if(&termios_release);
	exit(0);
}
