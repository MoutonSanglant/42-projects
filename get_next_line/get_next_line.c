/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 13:47:00 by tdefresn          #+#    #+#             */
/*   Updated: 2016/12/14 00:55:06 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		read_buffer(const int fd, char *buffer, char *buf)
{
	int		rcount;

	// si le buff n'est pas vide (multi-ligne dans le buffer)
	if (*buffer != '\0')
	{
		rcount = ft_strlen(buffer);
		ft_memcpy(buf, buffer, rcount);
		ft_bzero(buffer, BUFF_SIZE);
		buf[rcount] = '\0';
		return (rcount);
	}
	return (read(fd, buf, BUFF_SIZE));
}

static int		read_line(const int fd, char **line, char *buffer, size_t offset)
{
	char	buf[BUFF_SIZE + 1];
	char	*eol;
	int		length;
	int		rcount;

	if ((rcount = read_buffer(fd, buffer, buf)) < 0)
		return (-1);
	buf[rcount] = '\0';
	if (rcount == 0 && offset < 1)
		return (0);
	if (rcount == 0 || (eol = ft_strchr(buf, '\n')))
	{
		length = rcount;
		if (rcount)
		{
			rcount = eol - buf;
			ft_memmove(buffer, &buf[rcount + 1], length - rcount);
		}
		length = offset + rcount;
		*line = (char *)malloc(length + 1);
		(*line)[length] = '\0';
	}
	else if ((length = read_line(fd, line, buffer, offset + rcount)) <= 0)
		return (length); // -1
	ft_memcpy(&(*line)[offset], buf, rcount);
	return (1);
}

static int		index_lines(const int fd, char **line, t_gnl *p_fd, int idx)
{
	t_line	*last;
	t_line	*prev;
	int		ret;

	last = p_fd->lines;
	while (last && last->next)
		last = last->next;
	while (idx > p_fd->count)
	{
		if ((ret = read_line(fd, line, p_fd->buf, 0)) <= 0)
			return (ret);
		prev = last;
		if (!p_fd->lines
				&& (p_fd->lines = (t_line *)ft_memalloc(sizeof(t_line))))
			last = p_fd->lines;
		else if ((prev->next = (t_line *)ft_memalloc(sizeof(t_line))))
			last = prev->next;
		else
			return (-1);
		last->content = *line;
		p_fd->count++;
	}
	return (1);
}

static int		get_indexed_line(const int fd, char **line, t_gnl *p_fd, int idx)
{
	t_line	*link;
	int		ret;

	*line = NULL;
	if (idx < 0)
	{
		ft_putendl("[DEBUG] clean up !");
		ft_bzero(p_fd, sizeof(t_gnl));
		// TODO clean up
		//p_fd->lines = NULL;
		return (-1);
	}
	if ((ret = index_lines(fd, line, p_fd, idx)) <= 0)
		return (ret);
	p_fd->idx = idx + 1;
	link = p_fd->lines;
	while (--idx)
		link = link->next;
	*line = ft_strdup(link->content);
	return (1);
}

// 25 lignes + 3
int				get_next_line(const int fd, char **line)
{
	static t_gnl	fd_table[MAX_FD] = { [0 ... MAX_FD - 1] = { .fd = -1 } };
	t_gnl			*p_fd;
	int				rcount;

	if (fd < 0 || !line)
		return (-1);
	p_fd = fd_table;
	// on récupère, si il y en a une, la structure qui correspond au fd
	while (BUSY_FD(p_fd, fd) && p_fd < fd_table + MAX_FD - 1)
		p_fd++;
	// si fd négatif, pointeur nul, table fd pleine, échec !
	if (BUSY_FD(p_fd, fd))
		return (-1);
	// enregistrement du fd dans la structure
	p_fd->fd = fd;
	if (*line)
		p_fd->idx = ft_atoi(*line);
	// si le pointeur 'line' est utilisé
	if (p_fd->idx)
		return (get_indexed_line(fd, line, p_fd, p_fd->idx));

	//if (!get_line(p_fd, 0, line))
	if ((rcount = read_line(fd, line, p_fd->buf, 0)) <= 0)
	{
		ft_bzero(p_fd, sizeof(t_gnl));
		//ft_memdel(fd)
		return (rcount);
	}
	//p_fd->lines->content = NULL;
	return (1);
}
