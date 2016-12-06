/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 14:25:27 by tdefresn          #+#    #+#             */
/*   Updated: 2016/12/06 12:27:52 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	init_signals(void)
{
	int		sig;

	sig = SIGHUP;
	while (sig <= SIGUSR1)
	{
		if (sig == SIGKILL || sig == SIGSTOP)
		{
			sig++;
			continue ;
		}
		if (signal(sig, sig_handler) == SIG_ERR)
			fatal("can't catch signal %i", sig);
		sig++;
	}
}

void	sig_handler(int signo)
{
	if (signo == SIGWINCH)
	{
		refresh(NULL);
		return ;
	}
	if (signo == SIGCONT)
	{
		if (signal(SIGTSTP, sig_handler) == SIG_ERR)
			fatal("can't catch signal SIGTSTP");
		termios_if(&termios_raw);
		refresh(NULL);
	}
	else if (signo == SIGTSTP)
		termios_if(&termios_suspend);
	else
		quit();
}
