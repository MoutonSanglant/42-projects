/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 14:13:06 by tdefresn          #+#    #+#             */
/*   Updated: 2016/12/10 17:33:33 by tdefresn         ###   ########.fr       */
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

void	print_line(char **line, char **lineno, int ret)
{
	//printf("[line: %p]\n", *line);
	//printf("[lino: %p]\n", *lineno);
	if (ret <= 0)
		return ;
	printf("%sligne %s [%s%i%s]: %s%s\n", COLOR_BLUE, *lineno, COLOR_YELLOW, ret, COLOR_BLUE, *line, COLOR_NONE);
	if (*line != *lineno)
	{
		free(*line);
		*line = NULL;
		free(*lineno);
		*lineno = NULL;
	}
	else
	{
		*line = NULL;
		free(*lineno);
		*lineno = NULL;
	}
}

void	read_file(char *name)
{
	char	*line;
	char	*lineno_str;
	int		lineno;
	int		fd;
	int		ret;

	lineno = 0;
	write(1, COLOR_YELLOW, 5);
	write(1, READING_FILE, strlen(READING_FILE));
	write(1, COLOR_NONE, 5);
	write(1, "\n", 1);
	if ((fd = open(name, O_RDONLY)) < 0)
	{
		write(1, COULD_NOT_READ, strlen(COULD_NOT_READ));
		return ;
	}
	lineno_str = ft_itoa(lineno);
	line = lineno_str;
	//printf("lineno: %lli\n", line);
	while ((ret = get_next_line(fd, &line)))
	{
		if (ret < 0)
		{
			write(1, GNL_ERROR, strlen(GNL_ERROR));
			break ;
		}
		print_line(&line, &lineno_str, ret);
		lineno++;
		if (lineno == 3)
			break ;
		if (lineno == 2)
			lineno = 3;
		if (lineno == 4)
			lineno = 2;

		lineno_str = ft_itoa(lineno);
		line = lineno_str;
	}

	lineno_str = ft_itoa(4);
	line = lineno_str;
	ret = get_next_line(fd, &line);
	print_line(&line, &lineno_str, ret);

	lineno_str = ft_itoa(0);
	line = lineno_str;
	ret = get_next_line(fd, &line);
	print_line(&line, &lineno_str, ret);

	lineno_str = "-1";
	get_next_line(fd, &lineno_str);

	lineno_str = ft_itoa(4);
	line = lineno_str;
	ret = get_next_line(fd, &line);
	print_line(&line, &lineno_str, ret);
	//get_next_line(fd, &line);
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
