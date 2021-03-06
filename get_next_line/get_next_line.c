/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 13:47:00 by tdefresn          #+#    #+#             */
/*   Updated: 2017/01/19 16:22:47 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		get_next_datas(const int fd, char *left_over, char *buf)
{
	int		rcount;

	if (*left_over == '\0')
		rcount = read(fd, buf, BUFF_SIZE);
	else
	{
		rcount = ft_strlen(left_over);
		ft_memcpy(buf, left_over, rcount);
		ft_bzero(left_over, BUFF_SIZE);
	}
	buf[rcount] = '\0';
	return (rcount);
}

static int		read_line(const int fd, char **line, char *left_over,
															size_t offset)
{
	char	buf[BUFF_SIZE + 1];
	char	*eol;
	int		length;
	int		rcount;

	if ((rcount = get_next_datas(fd, left_over, buf)) < 0)
		return (-1);
	if (rcount == 0 && offset < 1)
		return (0);
	if (rcount == 0 || (eol = ft_strchr(buf, '\n')))
	{
		if (rcount)
		{
			length = rcount;
			rcount = eol - buf;
			ft_memmove(left_over, &buf[rcount + 1], length - rcount);
		}
		length = offset + rcount;
		*line = (char *)malloc(length + 1);
		(*line)[length] = '\0';
	}
	else if ((length = read_line(fd, line, left_over, offset + rcount)) <= 0)
		return (length);
	ft_memcpy(&(*line)[offset], buf, rcount);
	return ((rcount) ? rcount : 1);
}

static int		index_lines(const int fd, char **line, t_gnl *p_fd, int idx)
{
	t_line	*p_line;
	t_line	*p_prev;
	int		rcount;

	rcount = 1;
	p_line = p_fd->lines;
	while (p_line && p_line->next)
		p_line = p_line->next;
	while (idx > p_fd->count)
	{
		if ((rcount = read_line(fd, line, p_fd->buf, 0)) <= 0)
			return (rcount);
		p_prev = p_line;
		if (!(p_line = (t_line *)ft_memalloc(sizeof(t_line))))
			return (-1);
		else if (!p_fd->lines)
			p_fd->lines = p_line;
		else
			p_prev->next = p_line;
		p_line->content = *line;
		p_fd->count++;
	}
	return ((rcount) ? rcount : 1);
}

static int		get_indexed_line(const int fd, char **line, t_gnl *p_fd,
																	int idx)
{
	t_line	*p_line;
	int		rcount;

	*line = NULL;
	if (idx < 0)
	{
		while ((p_line = p_fd->lines))
		{
			p_fd->lines = p_line->next;
			ft_strdel(&p_line->content);
			ft_memdel((void **)p_line);
		}
		return (-1);
	}
	else if (idx == 0)
		idx = (p_fd->idx) ? p_fd->idx : 1;
	if ((rcount = index_lines(fd, line, p_fd, idx)) <= 0)
		return (rcount);
	p_fd->idx = idx + 1;
	p_line = p_fd->lines;
	while (--idx)
		p_line = p_line->next;
	*line = ft_strdup(p_line->content);
	return ((rcount = ft_strlen(*line)) ? rcount : 1);
}

int				get_next_line(const int fd, char **line)
{
	static t_gnl	fd_table[MAX_FD];
	t_gnl			*p_fd;
	int				rcount;

	if (fd < 0 || !line)
		return (-1);
	p_fd = fd_table;
	while (BUSY_FD(p_fd, fd) && p_fd < fd_table + MAX_FD - 1)
		p_fd++;
	if (BUSY_FD(p_fd, fd))
		return (-1);
	p_fd->busy = 1;
	p_fd->fd = fd;
	if (*line || p_fd->idx)
		rcount = get_indexed_line(fd, line, p_fd, ft_atoi(*line));
	else if ((rcount = read_line(fd, line, p_fd->buf, 0)) > 0)
		rcount = 1;
	if (rcount <= 0)
	{
		ft_bzero(p_fd, sizeof(t_gnl));
		p_fd->fd = -1;
		p_fd->busy = 0;
	}
	return (rcount);
}
