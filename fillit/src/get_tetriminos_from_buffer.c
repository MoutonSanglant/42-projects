/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tetriminos_from_buffer.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/18 19:56:10 by tdefresn          #+#    #+#             */
/*   Updated: 2016/09/17 23:01:39 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void		new_tetrimino(unsigned int mask, t_list **next,
										t_list **list, int last)
{
	t_tetrimino		*tetrimino;

	if (!(tetrimino = (t_tetrimino *)ft_memalloc(sizeof(t_tetrimino))))
		memory_error();
	tetrimino->mask.tetri = 0;
	tetrimino->mask.shifted = 0;
	tetrimino->mask.last = 0;
	tetrimino->mask.shift = 0;
	tetrimino->pattern_id = get_pattern_id(mask);
	tetrimino->h_shift = 0;
	tetrimino->v_shift = 0;
	if (*next)
	{
		(*next)->next = ft_lstnew(tetrimino, sizeof(*tetrimino));
		*next = (*next)->next;
	}
	else
	{
		*next = ft_lstnew(tetrimino, sizeof(*tetrimino));
		if (!last)
			*list = *next;
	}
	ft_memdel((void **)&tetrimino);
}

static void check_tetrimino_size(char **buffer, char *buffer_start,
				unsigned int *mask, unsigned short *height)
{
	unsigned short	width;

	width = 0;
	while (**buffer != '\n')
	{
		if (width > 3 || *height > 3)
			buffer_error(buffer_start);
		if (**buffer == '#')
			*mask |= 1 << (width + (*height * 4));
		else if (**buffer != '.')
			buffer_error(buffer_start);
		width++;
		(*buffer)++;
	}
	if (width < 4)
		buffer_error(buffer_start);
	(*height)++;
	(*buffer)++;
}

static void	read_buffer(char *buffer, char *buffer_start, t_list **list)
{
	t_list			*next;
	unsigned short	height;
	unsigned int	mask;

	next = NULL;
	mask = 0;
	height = 0;
	while (*buffer)
	{
		check_tetrimino_size(&buffer, buffer_start, &mask, &height);
		if (*buffer == '\n')
		{
			if (buffer[1] == '\0')
				error();
			new_tetrimino(mask, &next, list, 0);
			mask = 0;
			height = 0;
			buffer++;
		}
	}
	if (!mask)
		error();
	new_tetrimino(mask, &next, list, 1);
	if (!*list)
		*list = next;
}

t_list				*get_tetriminos_from_buffer(char *buffer)
{
	t_list			*list;

	list = NULL;
	read_buffer(buffer, buffer, &list);
	return (list);
}
