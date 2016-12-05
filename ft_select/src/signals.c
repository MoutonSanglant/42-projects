/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 14:25:27 by tdefresn          #+#    #+#             */
/*   Updated: 2016/12/05 15:39:24 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_select.h"

/*
** ft_printf("SIGHUP: %i\n", SIGHUP);
** ft_printf("SIGINT: %i\n", SIGINT);
** ft_printf("SIGQUIT: %i\n", SIGQUIT);
** ft_printf("SIGILL: %i\n", SIGILL);
** ft_printf("SIGTRAP: %i\n", SIGTRAP);
** ft_printf("SIGABRT: %i\n", SIGABRT);
** ft_printf("SIGEMT: %i\n", SIGEMT);
** ft_printf("SIGFPE: %i\n", SIGFPE);
** ft_printf("SIGKILL: %i\n", SIGKILL);
** ft_printf("SIGBUS: %i\n", SIGBUS);
** ft_printf("SIGSEGV: %i\n", SIGSEGV);
** ft_printf("SIGSYS: %i\n", SIGSYS);
** ft_printf("SIGPIPE: %i\n", SIGPIPE);
** ft_printf("SIGALRM: %i\n", SIGALRM);
** ft_printf("SIGTERM: %i\n", SIGTERM);
** ft_printf("SIGURG: %i\n", SIGURG);
** ft_printf("SIGSTOP: %i\n", SIGSTOP);
** ft_printf("SIGTSTP: %i\n", SIGTSTP);
** ft_printf("SIGCONT: %i\n", SIGCONT);
** ft_printf("SIGCHLD: %i\n", SIGCHLD);
** ft_printf("SIGTTIN: %i\n", SIGTTIN);
** ft_printf("SIGTTOU: %i\n", SIGTTOU);
** ft_printf("SIGIO: %i\n", SIGIO);
** ft_printf("SIGXCPU: %i\n", SIGXCPU);
** ft_printf("SIGXFSZ: %i\n", SIGXFSZ);
** ft_printf("SIGVTALRM: %i\n", SIGVTALRM);
** ft_printf("SIGPROF: %i\n", SIGPROF);
** ft_printf("SIGWINCH: %i\n", SIGWINCH);
** ft_printf("SIGINFO: %i\n", SIGINFO);
** ft_printf("SIGUSR1: %i\n", SIGUSR1);
** ft_printf("SIGUSR2: %i\n", SIGUSR2);
*/

void	init_signals()
{
	int		sig;

	sig = SIGHUP;
	while (sig <= SIGUSR2)
	{
		if (sig == SIGKILL || sig == SIGSTOP)
		{
			sig++;
			continue ;
		}
		if (signal(sig, sig_handler) == SIG_ERR)
			fatal("can't catch %i", sig);
		sig++;
	}
}

void	sig_handler(int signo)
{
	//ft_printf("Received signal: %i\n", signo);
	if (signo == SIGWINCH)
	{
		refresh(NULL);
		return ;
	}
	if (signo == SIGCONT)
	{
		if (signal(SIGTSTP, sig_handler) == SIG_ERR)
			fatal("can't catch SIGTSTP");
		termios_if(&termios_raw);
		refresh(NULL);
	}
	else if (signo == SIGTSTP)
		termios_if(&termios_suspend);
	else
	{
		printf("signal: %i // %i\n", signo, SIGFPE);
		quit();
	}
}
