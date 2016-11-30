/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 19:41:48 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/30 05:56:53 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/ioctl.h>

#include "termcap_macros.h"
#include "ft_select.h"

void	*termios_if(void *(*fn)(t_termios *))
{
	static t_termios	termios;

	return (fn(&termios));
}

void	*termios_get(t_termios *termios)
{
	return (termios);
}

/*
** Add ISIG to lflag for Signals
*/
void	*termios_raw(t_termios *termios)
{
	//isatty
	//ttyname
	//ttyslot
	termios->fd = open(ttyname(0), O_WRONLY);
	//tcgetattr(termios->fd, &termios->original);
	tcgetattr(termios->fd, &termios->original);
	//termios->fd = 1;
	//if (!isatty(termios->fd))
		//termios->fd = open(ttyname(0), O_WRONLY);
		//termios->fd = 2;
	termios->raw = termios->original;
	termios->raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	termios->raw.c_oflag &= ~(OPOST);
	termios->raw.c_cflag |= (CS8);
	termios->raw.c_lflag &= ~(ECHO | ICANON | IEXTEN);
	termios->raw.c_cc[VMIN] = 1;
	termios->raw.c_cc[VTIME] = 8;
	//if (tcsetattr(termios->fd, TCSAFLUSH, &termios->raw) < 0)
	//if (!isatty(1))
	if (!isatty(termios->fd))
		fatal("fd %i is not a valid tty.", termios->fd);
	if (tcsetattr(termios->fd, TCSAFLUSH, &termios->raw) < 0)
		fatal("can't set raw mode");
	TERM_CURSOR_HIDE(&ft_put);
	return (0);
}

void	*termios_release(t_termios *termios)
{
	TERM_CURSOR_SHOW(&ft_put);
	tcsetattr(termios->fd, TCSAFLUSH, &termios->original);
	close(termios->fd);
	return (0);
}

void	*termios_suspend(t_termios *termios)
{
	char	cmd[2];

	cmd[0] = termios->raw.c_cc[VSUSP];
	cmd[1] = '\0';
	signal(SIGTSTP, SIG_DFL);
	TERM_CURSOR_LINE_BEGIN(&ft_put);
	termios_if(&termios_release);
	ioctl(0, TIOCSTI, cmd);
	return (0);
}
