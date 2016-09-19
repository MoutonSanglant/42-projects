/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_stdin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/18 14:45:21 by tdefresn          #+#    #+#             */
/*   Updated: 2016/09/18 17:10:15 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "get_next_line.h"

/*
** Generic stdin reader with callback
*/
void read_stdin(int (callback)(char *, void *), void *st)
{
	char	*line;
	int		r;

	line = NULL;
	while((r = get_next_line(0, &line)))
	{
		if (r > 0)
		{
			if (callback(line, st))
				ft_memdel((void **)&line);
			else
			{
				ft_memdel((void **)&line);
				break ;
			}
		}
		else
		{
			memory_error();
		}
	}
}
