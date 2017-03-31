/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 16:18:02 by tdefresn          #+#    #+#             */
/*   Updated: 2017/03/29 20:03:00 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <unistd.h>

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "internal.h"
#include "malloc.h"

// pre_allocate
// small & medium mem area
// mem area must be a multiple of getpagesize()
// each area must AT LEAST contain 100 allocations
// TINY (1 to N bytes) -> to N bytes areas
// SMALL (N + 1 to M bytes) -> to M bytes areas
// LARGE (M + 1 and more) -> personnal areas

void	init_memory_maps()
{
	t_map				*map;
	t_malloc_map_type	type;
	size_t				bytes_left;

	type = MALLOC_MAP_TINY;
	while (type < MALLOC_MAP_LARGE + 1)
	{
		map = &g_maps[type];
		ft_bzero(map, sizeof(t_map));
		if (type == MALLOC_MAP_TINY)
		{
			map->size = 100;
			map->alloc_max_size = 1;
		}
		else if (type == MALLOC_MAP_SMALL)
		{
			map->size = 200;
			map->alloc_max_size = 2;
		}
		else if (type == MALLOC_MAP_LARGE)
		{
			map->size = 400;
			map->alloc_max_size = 4;
		}
		if ((bytes_left = map->size % getpagesize()))
			map->size += bytes_left;
		ft_putstr("[DEBUG] map: ");
		ft_putnbr(type);
		ft_putstr("\nsize = ");
		ft_putnbr(map->size);
		ft_putstr("\nalloc_max_size = ");
		ft_putnbr(map->alloc_max_size);
		ft_putendl("");
		type++;
		//printf("[DEBUG] map %i:\nsize = %lu\nalloc_max_size = %lu\n", type, map->size, map->alloc_max_size);
	}
}

void		*malloc(size_t size)
{
	static int	initialized = 0;
	void		*new_ptr;
	int			err;

	ft_putendl("entering malloc.");
	if (!initialized)
	{
		init_memory_maps();
		initialized = 1;
	}
	show_alloc_mem();
	(void)size;
	err = 0;
	// TODO:
	// read about last 3 arguments (flags, fdesc, off)
	//int fd = open() ???
	new_ptr = mmap(g_maps[0].data, size, PROT_READ | PROT_WRITE, MAP_SHARED, 1, 0);

	if (new_ptr == MAP_FAILED)
	{
		perror(strerror(errno));
		return(NULL);
	}
	if (err)
		return (NULL);
	return (new_ptr);
}
