/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 13:47:06 by tdefresn          #+#    #+#             */
/*   Updated: 2016/12/07 13:47:06 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <libft.h>

/*
** 167 is an arbitrary value set because it was my test program
** limit until the file size grows bigger
*/

# define BUFF_SIZE	128
# define MAX_FD		60


# define BUSY_FD(st, d) (st->fd >= 0 && st->fd != d)

typedef struct	s_line t_line;

struct	s_line
{
	char	*content;
	t_line	*next;
};
/*
** t_line:
** >> 8 + 8
**	= 16
*/

typedef struct	s_gnl
{
	char	buf[BUFF_SIZE + 1];
	t_line	*lines;
	int		count;
	int		idx;
	int		fd;
}				t_gnl;
/*
** t_gnl:
** >> 8 + 8 + (4 + 4) + (4 + ...)
**	= 32
*/

int		get_next_line(const int fd, char **line);

#endif
