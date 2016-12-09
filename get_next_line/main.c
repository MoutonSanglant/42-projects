/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 14:13:06 by tdefresn          #+#    #+#             */
/*   Updated: 2016/12/09 01:17:38 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "get_next_line.h"

#define READING_FILE "reading file: "
#define COULD_NOT_READ "error: could not read file\n"
#define GNL_ERROR "Error while reading file...\n"

#define COLOR_NONE "\033[0m"
#define COLOR_BLUE "\033[94m"
#define COLOR_YELLOW "\033[93m"

void	read_file(char *name)
{
	char	*line;
	long long int		lineno;
	int		fd;
	int		ret;

	lineno = 1;
	write(1, COLOR_YELLOW, 5);
	write(1, READING_FILE, strlen(READING_FILE));
	write(1, COLOR_NONE, 5);
	write(1, "\n", 1);
	if ((fd = open(name, O_RDONLY)) < 0)
	{
		write(1, COULD_NOT_READ, strlen(COULD_NOT_READ));
		return ;
	}
	line = 0x0 + (char *)lineno;
	line = NULL;
	line = 0x0 + (char *)0;
	//printf("lineno: %lli\n", line);
	while ((ret = get_next_line(fd, &line)))
	{
		if (ret < 0)
		{
			write(1, GNL_ERROR, strlen(GNL_ERROR));
			break ;
		}
		printf("%s%lli: %s%s\n", COLOR_BLUE, lineno, line, COLOR_NONE);
		free(line);
		line = NULL;
		lineno++;
		line = 0x0 + (char *)lineno;
		line = NULL;
	}
	close(fd);
}

int		main(int argc, char **argv)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		read_file(argv[i]);
		i++;
	}

	return (0);
}
