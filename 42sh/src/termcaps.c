/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 16:50:45 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/25 17:10:31 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		termcaps_init(struct termios *term)
{
	char			*name_term;

	name_term = getenv("TERM");
	if (tgetent(NULL, name_term) < 0)
		return (-1);
	if (tcgetattr(0, term) < 0)
		return (-1);
	printf("terminal: %s\n", name_term);
	return (0);
}
