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
** don't use too many/too big buffers as it will quickly consume stack
*/

# define BUFF_SIZE	128
# define MAX_FD		20
# define DATA_MAX_SIZE	80000000

# define BUSY_FD(st, d) (st->busy != 0 && st->fd != d)

# if MAX_FD * (BUFF_SIZE + 24) > DATA_MAX_SIZE
#  warning "Data segment too big ! Reduce buffer size or number of fd."
# endif

typedef struct s_line	t_line;

struct			s_line
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
	int		busy;
}				t_gnl;
/*
** t_gnl:
** >> 8 + 8 + (4 + 4) + (4 + 4)
**	= 32
*/

int				get_next_line(const int fd, char **line);

#endif
