/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_stdin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/18 14:45:21 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/17 08:36:14 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "get_next_line.h"

/*
** Generic stdin reader with callback 'read_line'
*/
void read_stdin(int (read_line)(char *, void *), void *st)
{
	char	*line;
	int		r;

	line = NULL;
	while((r = get_next_line(0, &line)))
	{
		if (r > 0)
		{
			r = read_line(line, st);
			ft_memdel((void **)&line);
			if (!r)
				break ;
		}
		else
			memerror();
	}
}
