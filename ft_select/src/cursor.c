/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 02:12:08 by tdefresn          #+#    #+#             */
/*   Updated: 2016/12/06 11:57:37 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcap_macros.h"
#include "ft_select.h"

/*
**  Query terminal for cursor position
*/

void	push_cursor(int i)
{
	while (i-- > 0)
		TERM_CURSOR_RIGHT(&ft_put);
}

void	get_cursor_position(int *x, int *y)
{
	char	buf[10];
	int		fd;
	int		ret;
	int		i;

	fd = 0;
	ft_dprintf(fd, "\033[6n");
	ret = read(fd, buf, 9);
	buf[ret] = '\0';
	i = 0;
	*y = ft_atoi(&buf[2]) - 1;
	while (buf[i] != ';')
		i++;
	*x = ft_atoi(&buf[i + 1]);
}
