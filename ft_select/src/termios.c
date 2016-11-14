/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 19:41:48 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/13 21:00:33 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

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

void	*termios_raw(t_termios *termios)
{
	termios->fd = open(ttyname(0), O_WRONLY);
	tcgetattr(termios->fd, &termios->original);
	termios->raw = termios->original;
	termios->raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	termios->raw.c_oflag &= ~(OPOST);
	termios->raw.c_cflag |= (CS8);
	termios->raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	termios->raw.c_cc[VMIN] = 5;
	termios->raw.c_cc[VTIME] = 8;
	termios->raw.c_cc[VMIN] = 0;
	termios->raw.c_cc[VTIME] = 0;
	termios->raw.c_cc[VMIN] = 2;
	termios->raw.c_cc[VTIME] = 0;
	termios->raw.c_cc[VMIN] = 0;
	termios->raw.c_cc[VTIME] = 8;
	if (tcsetattr(termios->fd,TCSAFLUSH, &termios->raw) < 0)
		fatal("can't set raw mode");
	return (0);
}

void	*termios_release(t_termios *termios)
{
	tcsetattr(termios->fd, TCSAFLUSH, &termios->original);
	close(termios->fd);
	return (0);
}
