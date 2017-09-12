/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 20:04:48 by tdefresn          #+#    #+#             */
/*   Updated: 2017/09/12 22:13:07 by mouton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

#include <fcntl.h>
#include <libftprintf.h>

#include "errors.h"
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

/*
static
void	parse_line(const char *line)
{
	if (line[0] == '#')
		return ;
	ft_printf("%s\n", line);
}

static
void	open_scene_file(const char *path)
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
*/

t_scene	*new_scene(const char *path)
{
	t_scene *scene;

	scene = (t_scene *)ft_memalloc(sizeof(t_scene));
	scene->path = path;

	return (scene);
}
