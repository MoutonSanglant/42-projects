/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 20:04:48 by tdefresn          #+#    #+#             */
/*   Updated: 2017/03/21 21:13:50 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>

#include "rtv1.h"
#include "get_next_line.h"

/*
list[] =
{
	&win_size_fn,
	&viewport_fn,
	&camera_fn,
	&ambient_fn,
	&light_sources_fn
	&transforms_fn
}
*/

void	parse_line(const char *line)
{
	if (line[0] == '#')
		return ;
	ft_printf("%s\n", line);
}

void	load_scene(const char *path)
{
	char	*line;
	int		ret;
	int		fd;

	line = NULL;
	if ((fd = open(path, O_RDONLY)) < 0)
		error(ERRNO_OPEN, path);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		parse_line(line);
		ft_strdel(&line);
	}
	if (ret < 0)
		error(ERRNO_READ, path);
	ft_strdel(&line);
}
