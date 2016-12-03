/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 13:05:18 by tdefresn          #+#    #+#             */
/*   Updated: 2016/12/03 10:51:45 by tdefresn         ###   ########.fr       */
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

int		ft_put(int c)
{
	write(((t_termios *)termios_if(&termios_get))->fd, &c, 1);
	return (1);
}

int		compute_col_width(char **list, int count)
{
	int		max;
	int		l;

	l = 0;
	max = 0;
	while (--count)
	{
		l = ft_strlen(list[count]);
		if (l > max)
			max = l;
	}
	return (max);
}

int		main(int argc, char **argv)
{
	t_select	select;

	if (argc < 2)
		return (0);

	init_signals();
	// select.tty is no more used
	//ft_bzero(&select.tty, sizeof(t_tty));
	ft_bzero(&select, sizeof(t_select));
	//set_tty(&select.tty);
	if (!init_terminal())
		return (1);
	termios_if(&termios_raw);
	//init_termcaps(select.tty.fd);
	//list_termcaps();
	//get_cursor_position(&select.cursor_x, &select.cursor_y);
	select.nb_elem = argc - 1;
	select.list = &argv[1];
	select.col_width = compute_col_width(select.list, select.nb_elem);
	refresh(&select);
	listen_input(&select);
	termios_if(&termios_release);
	print_list(&select);
	return (0);
}
