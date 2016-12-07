/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 13:47:00 by tdefresn          #+#    #+#             */
/*   Updated: 2016/12/07 18:28:08 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "get_next_line.h"

char	*find_eol(char *s)
{
	while (*s && *s != '\n')
		s++;
	return (s);
}

int		get_next_line(const int fd, char **line)
{
	static t_gnl	gnl_st;

	char	buf[BUFF_SIZE + 1];
	int		i;
	int		ret;
	char	*eol;
	int		wcount;

	if (fd < 0)
		return (-1);
	while ((ret = read(fd, buf, BUFF_SIZE)) >= 0)
	{
		eol = find_eol(buf);
		wcount = (int)(eol - buf);
		*line = malloc(wcount + 1);
		(*line)[wcount] = '\0';
		i = 0;
		while (i < wcount)
		{
			(*line)[i] = buf[i];
			i++;
		}
		if (ret == 0)
			return (0);
		return (1);
	}
	return (0);
}
