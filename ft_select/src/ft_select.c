/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 13:05:18 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/14 12:46:50 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** programme: ft_select
** reçoit une liste d'arguments
** la liste s'affiche
** l'utilisateur peut utiliser les flèches pour se déplacer dans la liste
** liste circulaire
** space: selectionner/déslectionne les elements
** suite à une selection, le curseur se trouve placé sur l'élément suivant'
** return: retourne la liste sélectionnée au shell, les éléments séparés par ' '
** (voir pdf: partie obligatoire)
** gérer redimensionnement fenetres
** ... explication bizarre sur le dimensions
** le programme ne quitte pas en cas de fenetre trop petite
** escape: quitte sans rien retourner
** delete/backspace: retire l'élément sélectionné de la liste. Si pas d'élément,
** comportement identique à escape
** couleurs:
** non sélectionné: normal
** sélectionné: video inverse
** position curseur: souligné
** sélectionné + position: vidéo inversé ET souligné
** en cas de signal: restaurer configuration terminal
** ctrl+z: suspend (restauré par 'fg')
** si env est vide, comportement raisonnable
** ====
** bonus
** =====
** fonctions autorisées:
** isatty
** ttyname
** ttyslot
** ioctl
** getenv*
** tcsetattr
** tcgetattr
** tgetent*
** tgetflag
** tgetnum
** tgetstr*
** tgoto
** tputs
** open
** close
** write
** malloc*
** sizeof*
** free*
** read
** exit*
** signal*
*/

/*
void	select_item()
{
	//move_cursor_next();
}
*/

#include <sys/ioctl.h>
#include <fcntl.h>
#include <ttyent.h>

#include "get_next_line.h"
#include "ft_select.h"


/*
** termtype: terminal type
** tgetent: terminal description (list of capabilities)
*/

int		init_terminal()
{
	char	*termtype;
	int		success;
	char	term_buffer[2048];

	termtype = getenv("TERM");
	if (termtype == 0)
		fatal("Specify a terminal type with `setenv TERM ...`.\n");
	success = tgetent(term_buffer, termtype);
	if (success < 0)
		fatal("Could not access the termcap data base.\n");
	if (success == 0)
		fatal("Terminal type %s is not defined.\n", termtype);
	return (1);
}

int		get_fd(void)
{
	static int fd;

	if (fd == 0)
		fd = open(ttyname(0), O_WRONLY);
	return (fd);
}

int		ft_put(int c)
{
	ft_putchar(c);
	return (1);
}

void	list_termcaps()
{
	int		pb_num;
	char	str[100];
	char	*cl_string;
	char	*cm_string;

	cl_string = tgetstr("cl", 0);
	cm_string = tgetstr("cm", 0);
	tputs(cl_string, 1, &ft_put);
	tputs(cm_string, 1, &ft_put);

	pb_num = tgetnum("pb");
	ft_snprintf(str, 100, "\npb: %i\n", pb_num);
	tputs(str, 1, &ft_put);
}

void	init_termcaps(int fd)
{
	(void)fd;
	ft_printf("unix mode\n");
	// use code TIOCLSET to set bit LLITOUT
	// use code TIOCSETN to clear bit ANYDELAY
	//ioctl(fd, TIOCLSET, LLITOUT);
}


int		get_tty_fd()
{
	struct ttyent	*t;
	int				slot;
	char	*nb;;

	slot = ttyslot();
	nb = ft_itoa(slot);

	while ((t = getttyent()))
	{
		if (t->ty_name)
		{
			if (ft_strequ(&t->ty_name[4], nb))
				break ;
		}
	}
	ft_printf("ty_name: %s\n", t->ty_name);
	ft_printf("ty_getty: %s\n", t->ty_getty);
	ft_printf("ty_type: %s\n", t->ty_type);
	ft_printf("ty_window: %s\n", t->ty_window);
	ft_printf("ty_comment: %s\n", t->ty_comment);
	return (slot);
}

void	set_tty(t_tty *tty)
{
	if (!isatty(tty->fd))
		fatal("fd %i is not a valid tty.", tty->fd);
	tty->name = ttyname(0);

	ft_printf("tty %s on fd %i\n", tty->name, tty->fd);
}


void	wait_for_input()
{
	while(1) // while !return
	{
		// if key...
	}
}


int		main(int argc, char **argv)
{
	t_tty	tty;

	(void)argv;

	if (argc < 2)
		return (0);
	if (signal(SIGINT, sig_handler) == SIG_ERR)
		fatal("can't catch SIGINT");
	if (signal(SIGQUIT, sig_handler) == SIG_ERR)
		fatal("can't catch SIGQUIT");

	ft_bzero(&tty, sizeof(t_tty));
	set_tty(&tty);
	if (!init_terminal())
		return (1);

	init_termcaps(tty.fd);
	termios_if(&termios_raw);
	//list_termcaps();

	ft_printf("Hello ");
	//tputs(tgetstr("IC", &a), 1, &ft_put); // insert N characters ?
	//tputs(tgetstr("im", 0), 1, &ft_put); // insert mode ?
	//tputs(tgetstr("al", 0), 1, &ft_put); // add line ?
	//tputs(tgoto(tgetstr("cm", 0), 10, 2), 1, &ft_put); // cursor move
	tputs(tgetstr("so", 0), 1, &ft_put); // standout on
	ft_printf("world");
	tputs(tgetstr("se", 0), 1, &ft_put); // standout end
	ft_printf(" !");
	tputs(tgetstr("do", 0), 1, &ft_put); // down
	tputs(tgetstr("cr", 0), 1, &ft_put); // cariage return
	wait_for_input();

	termios_if(&termios_release);
	return (0);
}
