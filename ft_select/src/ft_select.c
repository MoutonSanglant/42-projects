/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 13:05:18 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/12 13:24:31 by tdefresn         ###   ########.fr       */
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
** getenv
** tcsetattr
** tcgetattr
** tgetent
** tgetflag
** tgetnum
** tgetstr
** tgoto
** tputs
** open
** close
** write
** malloc
** sizeof
** free
** read
** exit
** signal
*/

void	select_item()
{
	//move_cursor_next();
}

int		maint(void)
{
	return (1);
}
