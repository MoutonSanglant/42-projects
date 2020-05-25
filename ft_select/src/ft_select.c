/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 13:05:18 by tdefresn          #+#    #+#             */
/*   Updated: 2016/12/06 13:40:42 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

#include "ft_select.h"

static int	compute_col_width(char **list, int count)
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
	return (max + 2);
}

/*
** termtype: terminal type
** tgetent: terminal description (list of capabilities)
*/

static void	init_terminal(void)
{
	char	*termtype;
	int		success;
	//char	term_buffer[2048];
	char	term_buffer[4096];

	termtype = getenv("TERM");
	ft_printf("termtype: %s\n", termtype);
	if (termtype == 0)
		fatal(ERR_TERM_NOT_DEFINED);
	success = tgetent(term_buffer, termtype);
	//ft_printf(term_buffer);
	if (success < 0)
		fatal(ERR_NO_TERM_DB);
	if (success == 0)
		fatal(ERR_TERM_TYPE_UNDEFINED, termtype);
}

int			ft_put(int c)
{
	write(((t_termios *)termios_if(&termios_get))->fd, &c, 1);
	return (1);
}

/*
** Output to stout
*/

static void	print_output(t_select *select)
{
	t_list	*next;
	t_list	*l;
	int		fd;

	fd = 1;
	l = select->selected;
	while (l)
	{
		ft_dprintf(fd, "%s", (char *)l->content);
		next = l->next;
		if (next)
			write(fd, " ", 1);
		ft_memdel((void *)&l->content);
		ft_memdel((void *)&l);
		l = next;
	}
	select->selected = NULL;
}

int			main(int argc, char **argv)
{
	t_select	select;
	int			args_count;

	if (argc < 2)
		return (0);
	ft_bzero(&select, sizeof(t_select));
	args_count = parse_arguments(argc, argv, &select);
	init_terminal();
	init_signals();
	termios_if(&termios_raw);
	select.nb_elem = argc - args_count;
	select.list = &argv[args_count];
	select.col_width = compute_col_width(select.list, select.nb_elem);
	//ft_printf("\nwidth: %i\n", select.col_width);

/*	
	refresh(&select);

/*/	
	char* buffer = malloc(2048);
	tputs(tgetstr("cr", &buffer), 1, &ft_put);
	ft_printf("Flag: %i\n", tgetflag("am"));
	tputs(tgetstr("cr", &buffer), 1, &ft_put);
	ft_printf("Numeric: %i\n", tgetnum("it"));
	tputs(tgetstr("cr", &buffer), 1, &ft_put);
	char* cap1 = tgetstr("us", &buffer);
	char* cap2 = tgetstr("ue", &buffer);
	char* cap3 = tgetstr("ke", &buffer);
	ft_printf("String: %s (%p), %s (%p), %s (%p)\n", cap1, cap1, cap3, cap3, cap2, cap2);
	int fd = ((t_termios *)termios_if(&termios_get))->fd;
	tputs(tgetstr("kh", &buffer), 1, &ft_put);
	tputs(tgetstr("ve", &buffer), 1, &ft_put);
	tputs(tgetstr("cr", &buffer), 1, &ft_put);
	tputs(cap1, 1, &ft_put);
	write(fd, "hello", 5);
	tputs(tgetstr("nd", &buffer), 1, &ft_put);
	tputs(tgetstr("nd", &buffer), 1, &ft_put);
	tputs(tgetstr("nd", &buffer), 1, &ft_put);
	tputs(tgetstr("nd", &buffer), 1, &ft_put);
	tputs(tgetstr("nd", &buffer), 1, &ft_put);
	write(fd, "hello", 5);
	tputs(cap2, 1, &ft_put);
	ft_printf("\n-----------\n");
	//clear(&select);
	termios_if(&termios_release);
	return (0);
//*/
 
	listen_input(&select);
	clear(&select);
	termios_if(&termios_release);
	print_output(&select);
	return (0);
}
